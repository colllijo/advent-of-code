#include "2024/Day04.hpp"

#include <numeric>
#include <string>

#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"

Day04_2024::Day04_2024()
{
	exampleInput =
	    "MMMSXXMASM\n"
	    "MSAMXMSMSA\n"
	    "AMXSXMAAMM\n"
	    "MSAMASMSMX\n"
	    "XMASAMXAMM\n"
	    "XXAMMXXAMA\n"
	    "SMSMSASXSS\n"
	    "SAXAMASAAA\n"
	    "MAMMMXMMMM\n"
	    "MXMXAXMASX";
}

string Day04_2024::part1(const string& input, bool example)
{
	string search = "XMAS";
	int count = 0;
	caoc::structs::Grid<char> grid(input);

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			for (const auto& dir : caoc::structs::Directions)
			{
				try
				{
					for (int i = 0; i < search.size(); i++)
					{
						if (grid.move(x, y, dir, i) != search[i]) goto next;
					}

					count++;
				}
				catch (const std::out_of_range&)
				{
				}

			next:
			}
		}
	}

	return to_string(count);
}

string Day04_2024::part2(const string& input, bool example)
{
	long long count = 0;
	caoc::structs::Grid<char> grid(input);

	auto crossCount = [&grid](int x, int y)
	{
		using caoc::structs::Direction;
		std::vector<Direction> diagonals = {Direction::NORTH_EAST, Direction::SOUTH_EAST, Direction::SOUTH_WEST, Direction::NORTH_WEST};

		return accumulate(diagonals.begin(), diagonals.end(), 0,
		                  [&grid, &x, &y](int acc, Direction dir) { return acc + (grid.move(x, y, dir, 1) == 'M' && grid.move(x, y, dir, -1) == 'S'); });
	};

	for (int y = 1; y < grid.height() - 1; y++)
	{
		for (int x = 1; x < grid.width() - 1; x++)
		{
			if (grid(x, y) != 'A') continue;
			if (crossCount(x, y) >= 2) count++;
		}
	}

	return to_string(count);
}
