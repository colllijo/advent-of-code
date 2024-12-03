#include "2024/Day03.hpp"

#include <regex>

Day03_2024::Day03_2024() { exampleInput = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))"; }

string Day03_2024::part1(const string& input, bool example)
{
	unsigned long result = 0;

	regex pattern(R"((mul\((\d+),(\d+)\)))");
	auto mBegin = sregex_iterator(input.begin(), input.end(), pattern);
	auto mEnd = sregex_iterator();

	if (mBegin == mEnd)
	{
		return "0";
	}

	for (sregex_iterator i = mBegin; i != mEnd; ++i)
	{
		smatch match = *i;

		int left = stoi(match.str().substr(4, match.str().find(',') - 1));
		int right = stoi(match.str().substr(match.str().find(',') + 1));

		result += left * right;
	}

	return to_string(result);
}

string Day03_2024::part2(const string& input, bool example)
{
	unsigned long result = 0;
	bool enabled = true;

	regex pattern(R"((mul\((\d+),(\d+)\)|do\(\)|don't\(\)))");
	auto mBegin = sregex_iterator(input.begin(), input.end(), pattern);
	auto mEnd = sregex_iterator();

	if (mBegin == mEnd)
	{
		return "0";
	}

	for (sregex_iterator i = mBegin; i != mEnd; ++i)
	{
		smatch match = *i;

		if (match.str().starts_with("do()"))
		{
			enabled = true;
		}
		else if (match.str().starts_with("don't()"))
		{
			enabled = false;
		}
		else if (match.str().starts_with("mul") && enabled)
		{
			int left = stoi(match.str().substr(4, match.str().find(',') - 1));
			int right = stoi(match.str().substr(match.str().find(',') + 1));

			result += left * right;
		}
	}

	return to_string(result);
}
