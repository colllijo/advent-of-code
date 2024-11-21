#include "2016/Day05.hpp"

#include "coll-aoc-runner/crypto/MD5.hpp"

Day05_2016::Day05_2016() { exampleInput = "abc"; }

string Day05_2016::part1(const string& input, bool example)
{
	int i = 1;

	string password = "";

	while (i > 0)
	{
		string hash = caoc::crypto::md5(input + to_string(i));
		if (hash.starts_with("00000"))
		{
			password += hash[5];
			if (password.length() == 8) break;
		}

		i++;
	}

	return password;
}

string Day05_2016::part2(const string& input, bool example)
{
	unsigned long i = 0;

	string password = "        ";
	int chars = 0;

	for (;;)
	{
		i++;
		string hash = caoc::crypto::md5(input + to_string(i));
		if (hash.starts_with("00000"))
		{
			if (hash[5] < '0' || hash[5] > '7' || password[hash[5] - '0'] != ' ')
			{
				continue;
			}

			password[hash[5] - '0'] = hash[6];
			if (++chars == 8) break;
		}
	}

	return password;
}
