#include "2016/Day07.hpp"

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

Day07_2016::Day07_2016()
{
	exampleInput =
	    "abba[mnop]qrst\n"
	    "abcd[bddb]xyyx\n"
	    "aaaa[qwer]tyui\n"
	    "ioxxoj[asdfgh]zxcvbn\n";

	exampleInput =
	    "aba[bab]xyz\n"
	    "xyx[xyx]xyx\n"
	    "aaa[kek]eke\n"
	    "zazbz[bzb]cdb\n";
}

string Day07_2016::part1(const string& input, bool example)
{
	int count = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		int brackCount = 0;
		bool found = false;

		for (int i = 0; i < line.size() - 3; i++)
		{
			if (line[i] == '[') brackCount++;
			if (line[i] == ']') brackCount--;
			if (line[i] == line[i + 3] && line[i + 1] == line[i + 2] && line[i] != line[i + 1])
			{
				if (brackCount == 0)
				{
					if (example) printf("Found %c%c%c%c\n", line[i], line[i + 1], line[i + 2], line[i + 3]);
					found = true;
				}
				else
				{
					found = false;
					break;
				}
			}
		}

		if (found)
		{
			count++;
		}
	}

	return to_string(count);
}

string Day07_2016::part2(const string& input, bool example)
{
	int count = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		int brackCount = 0;

		vector<pair<char, char>> abas{};
		vector<pair<char, char>> babs{};

		for (int i = 0; i < line.size() - 2; i++)
		{
			if (line[i] == '[') brackCount++;
			if (line[i] == ']') brackCount--;

			if (line[i] == line[i + 2] && line[i] != line[i + 1])
			{
				if (brackCount == 0)
				{
					abas.push_back({line[i], line[i + 1]});
				}
				else
				{
					babs.push_back({line[i], line[i + 1]});
				}
			}
		}

		bool found = false;
		for (const auto aba : abas)
		{
			for (const auto bab : babs)
			{
				if (aba.first == bab.second && aba.second == bab.first)
				{
					count++;
					goto end_loop;
				}
			}
		}

	end_loop:
	}

	return to_string(count);
}
