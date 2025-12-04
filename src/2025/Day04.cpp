#include "2025/Day04.hpp"

#include <print>
#include <string>

#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

Day04_2025::Day04_2025()
{
	exampleInput =
	    "..@@.@@@@.\n"
	    "@@@.@.@.@@\n"
	    "@@@@@.@.@@\n"
	    "@.@@@@..@.\n"
	    "@@.@@@@.@@\n"
	    ".@@@@@@@.@\n"
	    ".@.@.@.@@@\n"
	    "@.@@@.@@@@\n"
	    ".@@@@@@@@.\n"
	    "@.@.@@@.@.";
}

string Day04_2025::part1(const string& input, bool example)
{
	std::uint64_t result = 0;
	caoc::structs::Grid<char> grid(input);

	for (int y = 0; y < grid.height(); ++y)
	{
		for (int x = 0; x < grid.height(); ++x)
		{
			if (grid.get(x, y) != '@') { continue; }

			int paperRolls = 0;
			for (const auto& dir : Directions)
			{
				if (grid.inBounds(Vector2<int>(x, y) + dir.direction()) && grid.move(x, y, dir) == '@') { paperRolls++; }
			}

			if (paperRolls < 4) { result++; }
		}
	}

	return std::to_string(result);
}

string Day04_2025::part2(const string& input, bool example)
{
	std::uint64_t result = 0, prevResult = result;
	caoc::structs::Grid<char> grid(input);

	do
	{
		prevResult = result;
		for (int y = 0; y < grid.height(); ++y)
		{
			for (int x = 0; x < grid.height(); ++x)
			{
				if (grid.get(x, y) != '@') { continue; }

				int paperRolls = 0;
				for (const auto& dir : Directions)
				{
					if (grid.inBounds(Vector2<int>(x, y) + dir.direction()) && grid.move(x, y, dir) == '@') { paperRolls++; }
				}

				if (paperRolls < 4)
				{
					grid.set(x, y, 'x');
					result++;
				}
			}
		}
	} while (result > prevResult);

	return std::to_string(result);
}
