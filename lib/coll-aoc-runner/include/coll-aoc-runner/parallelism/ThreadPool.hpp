#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>
namespace caoc::parallelism
{
	class ThreadPool
	{
	public:
		ThreadPool(size_t threads = std::thread::hardware_concurrency());
    ~ThreadPool();
  
    template <typename F, typename... Args>
    auto enqueue(F&&, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

	private:
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;

    std::mutex m_mutex;
    std::condition_variable m_condition;
    bool m_stop = false;
	};

  inline ThreadPool::ThreadPool(size_t threads): m_stop(false)
  {
    for (size_t i = 0; i < threads; i++)
    {
      m_workers.emplace_back([this] {
        for (;;) 
        {
          std::function<void()> task;

          {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condition.wait(lock, [this] { return m_stop || !m_tasks.empty(); });

            if (m_stop && m_tasks.empty()) return;

            task = std::move(m_tasks.front());
            m_tasks.pop();
          }

          task();
        }
      });
    }
  }

  inline ThreadPool::~ThreadPool()
  {
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      m_stop = true;
    }

    m_condition.notify_all();
    for (std::thread& worker : m_workers) worker.join();
  }

  template <typename F, typename... Args>
  auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type>
  {
    using returnType = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<returnType()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<returnType> res = task->get_future();

    {
      std::unique_lock<std::mutex> lock(m_mutex);
      if (m_stop) throw std::runtime_error("enqueue on stopped ThreadPool");

      m_tasks.emplace([task] { (*task)(); });
    }

    m_condition.notify_one();
    return res;
  }
};  // namespace caoc::parallelism
