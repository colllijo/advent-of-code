#include "2024/Day14.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace caoc;
using namespace caoc::structs;

Day14_2024::Day14_2024()
{
	exampleInput =
	    "p=0,4 v=3,-3\n"
	    "p=6,3 v=-1,-3\n"
	    "p=10,3 v=-1,2\n"
	    "p=2,0 v=2,-1\n"
	    "p=0,0 v=1,3\n"
	    "p=3,0 v=-2,-2\n"
	    "p=7,6 v=-1,-3\n"
	    "p=3,0 v=-1,-2\n"
	    "p=9,3 v=2,3\n"
	    "p=7,3 v=-1,2\n"
	    "p=2,4 v=2,-3\n"
	    "p=9,5 v=-3,-3";
}

string Day14_2024::part1(const string& input, bool example)
{
	vector<pair<Vector2<int>, Vector2<int>>> robots;

	for (const auto& line : strings::split(input, "\n"))
	{
		smatch match;
		if (regex_search(line, match, regex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))")))
		{
			int x = stoi(match[1]);
			int y = stoi(match[2]);
			int vx = stoi(match[3]);
			int vy = stoi(match[4]);

			robots.push_back({{x, y}, {vx, vy}});
		}
	}

	int width = example ? 11 : 101;
	int height = example ? 7 : 103;

	for (int i = 0; i < 100; i++)
	{
		for (auto& robot : robots)
		{
			robot.first += robot.second;

			robot.first.setX((robot.first.x() + width) % width);
			robot.first.setY((robot.first.y() + height) % height);
		}
	}

	vector<int> quadrants(4, 0);
	for (const auto& robot : robots)
	{
		if (robot.first.x() < width / 2 && robot.first.y() < height / 2)
		{
			quadrants[0]++;
		}
		else if (robot.first.x() > width / 2 && robot.first.y() < height / 2)
		{
			quadrants[1]++;
		}
		else if (robot.first.x() < width / 2 && robot.first.y() > height / 2)
		{
			quadrants[2]++;
		}
		else if (robot.first.x() > width / 2 && robot.first.y() > height / 2)
		{
			quadrants[3]++;
		}
	}

	return to_string(accumulate(quadrants.begin(), quadrants.end(), 1, multiplies<int>()));
}

string Day14_2024::part2(const string& input, bool example)
{
	const int MAX_ITERATIONS = 10000;
	const int MIN_FRAME_WIDTH = 25;

	vector<pair<Vector2<int>, Vector2<int>>> robots;

	for (const auto& line : strings::split(input, "\n"))
	{
		smatch match;
		if (regex_search(line, match, regex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))")))
		{
			int x = stoi(match[1]);
			int y = stoi(match[2]);
			int vx = stoi(match[3]);
			int vy = stoi(match[4]);

			robots.push_back({{x, y}, {vx, vy}});
		}
	}

	int width = example ? 11 : 101;
	int height = example ? 7 : 103;

	Grid<char> grid(width, height, ' ');
	for (int i = 0; i < MAX_ITERATIONS; i++)
	{
		for (auto& robot : robots)
		{
			grid.set(robot.first, ' ');
			robot.first += robot.second;

			robot.first.setX((robot.first.x() + width) % width);
			robot.first.setY((robot.first.y() + height) % height);
			grid.set(robot.first, '#');
		}

		for (const auto& row : grid.rows())
		{
			int maxLength = 0;
			int currentLength = 0;

			for (char c : row)
			{
				if (c == '#')
				{
					currentLength++;
				}
				else
				{
					if (currentLength > maxLength)
					{
						maxLength = currentLength;
					}
					currentLength = 0;
				}
			}

			if (maxLength >= MIN_FRAME_WIDTH)
			{
				return to_string(i + 1);
			}
		}
	}

	return "Solution not found: Maybe tweak the constants";
}
