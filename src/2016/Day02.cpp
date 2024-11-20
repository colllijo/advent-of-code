#include "2016/Day02.hpp"

#include <sstream>
#include <vector>

Day02_2016::Day02_2016()
{
	exampleInput =
	    "ULL\n"
	    "RRDDD\n"
	    "LURDL\n"
	    "UUUUD\n";
}

string Day02_2016::part1(const string& input, bool example)
{
	string code = "";
	vector<vector<char>> keypad = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
	pair<int, int> position = {1, 1};

	auto move = [&](const char direction)
	{
		switch (direction)
		{
			case 'U':
				position.first = max(0, position.first - 1);
				break;
			case 'D':
				position.first = min(2, position.first + 1);
				break;
			case 'L':
				position.second = max(0, position.second - 1);
				break;
			case 'R':
				position.second = min(2, position.second + 1);
				break;
		}
	};

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		for (const auto c : line)
		{
			move(c);
		}
		code += keypad[position.first][position.second];
	}

	return code;
}

string Day02_2016::part2(const string& input, bool example)
{
	string code = "";
	vector<vector<char>> keypad = {
    {'\0', '\0', '1', '\0', '\0'},
    {'\0', '2', '3', '4', '\0'},
    {'5', '6', '7', '8', '9'},
    {'\0', 'A', 'B', 'C', '\0'},
    {'\0', '\0', 'D', '\0', '\0'},
  };
	pair<int, int> position = {0, 2};

	auto move = [&](const char direction)
	{
    int x;

		switch (direction)
		{
			case 'U':
				x = max(0, position.first - 1);
        if (keypad[x][position.second] != '\0') position.first = x;
				break;
			case 'D':
				x = min(4, position.first + 1);
        if (keypad[x][position.second] != '\0') position.first = x;
				break;
			case 'L':
				x = max(0, position.second - 1);
        if (keypad[position.first][x] != '\0') position.second = x;
				break;
			case 'R':
				x = min(4, position.second + 1);
        if (keypad[position.first][x] != '\0') position.second = x;
				break;
		}
	};

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		for (const auto c : line)
		{
			move(c);
		}
		code += keypad[position.first][position.second];
	}

	return code;
}
