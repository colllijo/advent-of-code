#include "2024/Day19.hpp"

#include <algorithm>
#include <numeric>
#include "coll-aoc-runner/parallelism/ThreadPool.hpp"

Day19_2024::Day19_2024()
{
	exampleInput =
	    "r, wr, b, g, bwu, rb, gb, br\n"
	    "\n"
	    "brwrr\n"
	    "bggr\n"
	    "gbbr\n"
	    "rrbgbr\n"
	    "ubwu\n"
	    "bwurrg\n"
	    "brgr\n"
	    "bbrgwb";
}

string Day19_2024::part1(const string& input, bool example) { 
	parallelism::ThreadPool pool{};
	vector<future<bool>> futures{};
	unordered_set<string> towels{};

	for (const auto& towl : strings::split(strings::split(input, "\n\n")[0], ", "))
		towels.insert(towl);

	for (const auto& design : strings::split(strings::split(input, "\n\n")[1], "\n"))
	{
		futures.emplace_back(pool.enqueue([](const string& s, const unordered_set<string>& substrings) -> bool {
			vector<bool> dp(s.size() + 1, false);
			dp[0] = true;

			for (size_t i = 1; i < dp.size(); i++)
			{
				for (const auto& sub : substrings)
				{
					size_t len = sub.size();
					if (i >= len && s.substr(i - len, len) == sub)
						dp[i] = dp[i] || dp[i - len];
				}
			}

			return dp[s.size()];
		}, design, towels));
	}

	return to_string(accumulate(futures.begin(), futures.end(), 0, [](int sum, future<bool>& f) {
		return sum + f.get();
	}));
}

string Day19_2024::part2(const string& input, bool example)
{
	parallelism::ThreadPool pool{};
	vector<future<unsigned long long>> futures{};
	unordered_set<string> towels{};

	for (const auto& towl : strings::split(strings::split(input, "\n\n")[0], ", "))
		towels.insert(towl);

	for (const auto& design : strings::split(strings::split(input, "\n\n")[1], "\n"))
	{
		futures.emplace_back(pool.enqueue([](const string& s, const unordered_set<string>& substrings) -> unsigned long long {
			vector<unsigned long long> dp(s.size() + 1, false);
			dp[0] = true;

			for (size_t i = 1; i < dp.size(); i++)
			{
				for (const auto& sub : substrings)
				{
					size_t len = sub.size();
					if (i >= len && s.substr(i - len, len) == sub)
						dp[i] += dp[i - len];
				}
			}

			return dp[s.size()];
		}, design, towels));
	}

	return to_string(accumulate(futures.begin(), futures.end(), 0ULL, [](unsigned long long sum, future<unsigned long long>& f) {
		return sum + f.get();
	}));

}
