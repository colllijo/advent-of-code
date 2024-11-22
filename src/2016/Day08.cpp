#include "2016/Day08.hpp"

#include <array>
#include <sstream>

Day08_2016::Day08_2016()
{
	exampleInput =
	    "rect 3x2\n"
	    "rotate column x=1 by 1\n"
	    "rotate row y=0 by 4\n"
	    "rotate column x=1 by 1\n";
}

void rect(array<array<bool, 50>, 6>& screen, string grid)
{
	auto x = stoi(grid.substr(0, grid.find('x')));
	auto y = stoi(grid.substr(grid.find('x') + 1));

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			screen[i][j] = true;
		}
	}
};

void rotCol(array<array<bool, 50>, 6>& screen, string ins)
{
	auto col = stoi(ins.substr(0, ins.find(' ')));
	auto by = stoi(ins.substr(ins.find(' ') + 4));

	array<bool, 6> temp{};
	for (int i = 0; i < 6; i++)
	{
		temp[(i + by) % 6] = screen[i][col];
	}
	for (int i = 0; i < 6; i++)
	{
		screen[i][col] = temp[i];
	}
};

void rotRow(array<array<bool, 50>, 6>& screen, string ins)
{
	auto row = stoi(ins.substr(0, ins.find(' ')));
	auto by = stoi(ins.substr(ins.find(' ') + 4));

	array<bool, 50> temp{};
	for (int i = 0; i < 50; i++)
	{
		temp[(i + by) % 50] = screen[row][i];
	}
	for (int i = 0; i < 50; i++)
	{
		screen[row][i] = temp[i];
	}
};

string Day08_2016::part1(const string& input, bool example)
{
	array<array<bool, 50>, 6> screen{};

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.starts_with("rect"))
		{
			rect(screen, line.substr(5));
		}
		else if (line.starts_with("rotate column"))
		{
			rotCol(screen, line.substr(16));
		}
		else if (line.starts_with("rotate row"))
		{
			rotRow(screen, line.substr(13));
		}
	}

	int lit = 0;
	for (const auto& row : screen)
	{
		for (const auto& cell : row)
		{
			if (cell) lit++;
		}
	}

	return to_string(lit);
}

string Day08_2016::part2(const string& input, bool example)
{
	array<array<bool, 50>, 6> screen{};

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.starts_with("rect"))
		{
			rect(screen, line.substr(5));
		}
		else if (line.starts_with("rotate column"))
		{
			rotCol(screen, line.substr(16));
		}
		else if (line.starts_with("rotate row"))
		{
			rotRow(screen, line.substr(13));
		}
	}

  string img = "\n";
	for (const auto& row : screen)
	{
		for (const auto& cell : row)
		{
			img += cell ? "█" : " ";
		}
    img += "\n";
	}

	return img;
}
