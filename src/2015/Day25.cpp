#include "2015/Day25.hpp"

#include <regex>
#include <string>

Day25_2015::Day25_2015() { exampleInput = "To continue, please consult the code grid in the manual.  Enter the code at row 3, column 4."; }

long long modExp(long long base, long long exp, long long mod)
{
	long long res = 1;

	base %= mod;
	if (base == 0)
	{
		return 0;
	}

	while (exp > 0)
	{
		if ((exp & 0b1) == 1)
		{
			res = (res * base) % mod;
		}

		exp >>= 1;
		base = (base * base) % mod;
	}

	return res;
}

long long calculateCode(int row, int col)
{
	long long index = static_cast<long long>(1.0 + static_cast<double>(row) / 2.0 * static_cast<double>(row - 1)) +
	                  static_cast<long long>(static_cast<double>((1 + row) + (col + row - 1)) / 2.0 * static_cast<double>(col - 1));

	return (static_cast<long long>(20151125) * modExp(static_cast<long long>(252533), index - 1, static_cast<long long>(33554393))) % 33554393;
}

string Day25_2015::part1(const string& input, bool example)
{
  smatch match;
  if (regex_search(input, match, regex(R"(row (\d+), column (\d+))")))
  {
    long long row = stoll(match[1].str());
    long long col = stoll(match[2].str());

    return to_string(calculateCode(row, col));
  }

	return "Bad input.";
}

string Day25_2015::part2(const string& input, bool example) { return "Nothing to do, snow falls"; }
