#include "2025/Day07.hpp"

#include <algorithm>
#include <functional>
#include <print>

#include "coll-aoc-runner/structs/Grid.hpp"

Day07_2025::Day07_2025()
{
	exampleInput = ".......S.......\n"
				   "...............\n"
				   ".......^.......\n"
				   "...............\n"
				   "......^.^......\n"
				   "...............\n"
				   ".....^.^.^.....\n"
				   "...............\n"
				   "....^.^...^....\n"
				   "...............\n"
				   "...^.^...^.^...\n"
				   "...............\n"
				   "..^...^.....^..\n"
				   "...............\n"
				   ".^.^.^.^.^...^.\n"
				   "...............";
}

string Day07_2025::part1(const string &input, bool example)
{
	std::int64_t result = 0;
	caoc::structs::Grid<char> tachyonManifold(input);

	for (std::size_t y = 0; y < tachyonManifold.height() - 1; ++y)
	{
		for (std::size_t x = 0; x < tachyonManifold.width(); ++x)
		{
			if (tachyonManifold.get(x, y) == '|' || tachyonManifold.get(x, y) == 'S')
			{
				if (tachyonManifold.get(x, y + 1) == '^')
				{
					result++;
					tachyonManifold.set(x + 1, y + 1, '|');
					tachyonManifold.set(x - 1, y + 1, '|');
				}
				else {
					tachyonManifold.set(x, y + 1, '|');
				}
			}
		}
	}

	return std::to_string(result);
}

string Day07_2025::part2(const string &input, bool example)
{
	std::int64_t result = 0;
	caoc::structs::Grid<std::int64_t> tachyonManifold(input,
		[](char c)
		{
			switch (c)
			{
			case 'S':
				return 1;
			case '^':
				return -1;
			default:
				return 0;
			}
		});

	for (std::size_t y = 0; y < tachyonManifold.height() - 1; ++y)
	{
		for (std::size_t x = 0; x < tachyonManifold.width(); ++x)
		{
			auto cell = tachyonManifold.get(x, y);
			if (cell > 0)
			{
				if (tachyonManifold.get(x, y + 1) == -1)
				{
					tachyonManifold.set(x + 1, y + 1, tachyonManifold.get(x + 1, y + 1) + cell);
					tachyonManifold.set(x - 1, y + 1, tachyonManifold.get(x - 1, y + 1) + cell);
				}
				else {
					tachyonManifold.set(x, y + 1, tachyonManifold.get(x, y + 1) + cell);
				}
			}
		}
	}

	return std::to_string(std::ranges::fold_left(tachyonManifold.row(tachyonManifold.height() - 1) | std::views::filter([](auto &&val) { return val != -1; }), 0, std::plus{}));
}
