#include "2024/Day10.hpp"

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"

Day10_2024::Day10_2024()
{
	exampleInput =
	    "89010123\n"
	    "78121874\n"
	    "87430965\n"
	    "96549874\n"
	    "45678903\n"
	    "32019012\n"
	    "01329801\n"
	    "10456732";
}

const vector<caoc::structs::Direction> dirs = {
    caoc::structs::Direction::NORTH,
    caoc::structs::Direction::SOUTH,
    caoc::structs::Direction::WEST,
    caoc::structs::Direction::EAST,
};

string Day10_2024::part1(const string& input, bool example)
{
	caoc::structs::Grid<int> grid(input, [](char c) { return c - '0'; });
	vector<pair<int, int>> pos;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == 0)
			{
				pos.push_back({x, y});
			}
		}
	}
	long long sum = 0;
	for (const auto& p : pos)
	{
		set<pair<int, int>> paths {p};

		int step = 1;
		while (step <= 9)
		{
			set<pair<int, int>> newPaths;
			for (const auto& [x, y] : paths)
			{
				for (const auto& dir : dirs)
				{
					int nx = x + dir.direction().first;
					int ny = y + dir.direction().second;
					if (grid.inBounds(nx, ny) && grid.get(nx, ny) == step)
					{
						newPaths.insert({nx, ny});
					}
				}
			}

			paths = newPaths;
			step++;
		}

		sum += paths.size();
	}

	return to_string(sum);
}

string Day10_2024::part2(const string& input, bool example)
{
	caoc::structs::Grid<int> grid(input, [](char c) { return c - '0'; });
	vector<pair<int, int>> pos;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == 0)
			{
				pos.push_back({x, y});
			}
		}
	}
	long long sum = 0;
	for (const auto& p : pos)
	{
		vector<pair<int, int>> paths {p};

		int step = 1;
		while (step <= 9)
		{
			vector<pair<int, int>> newPaths;
			for (const auto& [x, y] : paths)
			{
				for (const auto& dir : dirs)
				{
					int nx = x + dir.direction().first;
					int ny = y + dir.direction().second;
					if (grid.inBounds(nx, ny) && grid.get(nx, ny) == step)
					{
						newPaths.push_back({nx, ny});
					}
				}
			}

			paths = newPaths;
			step++;
		}

		sum += paths.size();
	}

	return to_string(sum);
}
