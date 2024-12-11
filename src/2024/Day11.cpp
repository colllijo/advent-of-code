#include "2024/Day11.hpp"

#include <future>
#include <numeric>
#include <sstream>
#include <vector>
#include "coll-aoc-runner/parallelism/ThreadPool.hpp"

Day11_2024::Day11_2024() { exampleInput = "125 17"; }

string Day11_2024::part1(const string& input, bool example)
{
	caoc::parallelism::ThreadPool pool;
	vector<future<size_t>> futureStones;
	vector<long long> stones;

	stringstream stream(input);
	string line;
	while (getline(stream, line, ' '))
	{
		stones.push_back(stoll(line));
	}

	for (const auto& stone : stones)
	{
		futureStones.push_back(pool.enqueue([](long long stone) {
			vector<long long> stones{ stone };

			for (int blinks = 0; blinks < 25; blinks++)
			{
				for (size_t i = 0; i < stones.size(); i++)
				{
					if (stones[i] == 0)
					{
						stones[i] = 1;
					}
					else if ((to_string(stones[i]).size() & 0b1) == 0)
					{
						long long left = stoll(to_string(stones[i]).substr(0, to_string(stones[i]).size() / 2));
						long long right = stoll(to_string(stones[i]).substr(to_string(stones[i]).size() / 2));

						stones[i] = left;
						stones.insert(stones.begin() + i + 1, right);
						i++;
					}
					else
					{
						stones[i] *= 2024;
					}
				}
			}

			return stones.size();
		}, stone));
	}

	return to_string(accumulate(futureStones.begin(), futureStones.end(), 0, [](size_t sum, future<size_t>& f) { return sum + f.get(); }));
}

string Day11_2024::part2(const string& input, bool example)
{
	caoc::parallelism::ThreadPool pool;
	vector<future<size_t>> futureStones;
	vector<long long> stones;

	stringstream stream(input);
	string line;
	while (getline(stream, line, ' '))
	{
		stones.push_back(stoll(line));
	}

	for (const auto& stone : stones)
	{
		futureStones.push_back(pool.enqueue([](long long stone) {
			vector<long long> stones{ stone };

			for (int blinks = 0; blinks < 75; blinks++)
			{
				for (size_t i = 0; i < stones.size(); i++)
				{
					if (stones[i] == 0)
					{
						stones[i] = 1;
					}
					else if ((to_string(stones[i]).size() & 0b1) == 0)
					{
						long long left = stoll(to_string(stones[i]).substr(0, to_string(stones[i]).size() / 2));
						long long right = stoll(to_string(stones[i]).substr(to_string(stones[i]).size() / 2));

						stones[i] = left;
						stones.insert(stones.begin() + i + 1, right);
						i++;
					}
					else
					{
						stones[i] *= 2024;
					}
				}
			}

			return stones.size();
		}, stone));
	}

	return to_string(accumulate(futureStones.begin(), futureStones.end(), 0, [](size_t sum, future<size_t>& f) { return sum + f.get(); }));
}
