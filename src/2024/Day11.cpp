#include "2024/Day11.hpp"

#include <future>
#include <mutex>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include "coll-aoc-runner/parallelism/ThreadPool.hpp"

Day11_2024::Day11_2024() { exampleInput = "125 17"; }

template <typename a, typename b>
struct hash<std::pair<a, b>>
{
private:
	const hash<a> ah;
	const hash<b> bh;

public:
	hash() : ah(), bh() {}
	size_t operator()(const std::pair<a, b>& p) const { return ah(p.first) ^ bh(p.second); }
};

unsigned long long getRockCount(long long stone, int blinks, unordered_map<pair<long long, int>, unsigned long long>& lookup, mutex& lookupMutex)
{
	if (blinks == 0) return 1;

  {
    lock_guard<mutex> lock(lookupMutex);
    if (lookup.find({stone, blinks}) != lookup.end())
    {
      return lookup[{stone, blinks}];
    }
  }

  auto ret = [&lookup, &lookupMutex, &stone, &blinks](unsigned long long val){
      lock_guard<mutex> lock(lookupMutex);
      lookup[{stone, blinks}] = val;
      return val;
  };

	if (stone == 0)
	{
		return ret(getRockCount(1, blinks - 1, lookup, lookupMutex));
	}
	if (to_string(stone).size() & 0b1)
	{
		return ret(getRockCount(stone * 2024, blinks - 1, lookup, lookupMutex));
	}
	else
	{
		long long left = stoll(to_string(stone).substr(0, to_string(stone).size() / 2));
		long long right = stoll(to_string(stone).substr(to_string(stone).size() / 2));

		return ret(getRockCount(left, blinks - 1, lookup, lookupMutex) + getRockCount(right, blinks - 1, lookup, lookupMutex));
	}
}

string Day11_2024::part1(const string& input, bool example)
{
	caoc::parallelism::ThreadPool pool;
	vector<future<unsigned long long>> futureStones;
	vector<long long> stones;

	unordered_map<pair<long long, int>, unsigned long long> lookup;
	mutex lookupMutex;

	stringstream stream(input);
	string line;
	while (getline(stream, line, ' ')) stones.push_back(stoll(line));

	for (const auto& stone : stones) futureStones.push_back(pool.enqueue([&lookup, &lookupMutex](long long stone) { return getRockCount(stone, 25, lookup, lookupMutex); }, stone));

	return to_string(accumulate(futureStones.begin(), futureStones.end(), 0, [](unsigned long long sum, future<unsigned long long>& f) { return sum + f.get(); }));
}

string Day11_2024::part2(const string& input, bool example)
{
	caoc::parallelism::ThreadPool pool;
	vector<future<unsigned long long>> futureStones;
	vector<long long> stones;

	unordered_map<pair<long long, int>, unsigned long long> lookup;
	mutex lookupMutex;

	stringstream stream(input);
	string line;
	while (getline(stream, line, ' ')) stones.push_back(stoll(line));

	for (const auto& stone : stones) futureStones.push_back(pool.enqueue([&lookup, &lookupMutex](long long stone) { return getRockCount(stone, 75, lookup, lookupMutex); }, stone));

	return to_string(accumulate(futureStones.begin(), futureStones.end(), 0ULL, [](unsigned long long sum, future<unsigned long long>& f) { return sum + f.get(); }));
}
