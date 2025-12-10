#include "2025/Day09.hpp"

#include <algorithm>
#include <cstdint>
#include <print>
#include <ranges>
#include <string>
#include <vector>

#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

Day09_2025::Day09_2025()
{
	exampleInput = "7,1\n"
				   "11,1\n"
				   "11,7\n"
				   "9,7\n"
				   "9,5\n"
				   "2,5\n"
				   "2,3\n"
				   "7,3";
}

using caoc::structs::Grid;
using caoc::structs::Vector2;

string Day09_2025::part1(const string &input, bool example)
{
	std::vector<Vector2<std::int64_t>> tiles = std::ranges::to<std::vector<Vector2<std::int64_t>>>(
		input | std::views::split('\n') |
		std::views::transform(
			[](auto &&line)
			{
				auto nums = std::ranges::to<std::vector<std::string>>(line | std::views::split(',')) | std::views::transform([](auto &&val) { return std::stoll(val); });
				auto it	  = nums.begin();

				return Vector2<std::int64_t>{*it, *(++it)};
			}));

	std::int64_t area = 0;

	for (std::size_t i = 0; i < tiles.size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < tiles.size(); ++j) { area = std::max(area, (std::abs(tiles[i].x() - tiles[j].x()) + 1) * (std::abs(tiles[i].y() - tiles[j].y()) + 1)); }
	}

	return std::to_string(area);
}

string Day09_2025::part2(const string &input, bool example)
{
	if (!example) { return "TODO: Solve"; }

	std::int64_t maxX = 0, maxY = 0;

	std::vector<Vector2<std::int64_t>> tiles = std::ranges::to<std::vector<Vector2<std::int64_t>>>(
		input | std::views::split('\n') |
		std::views::transform(
			[&maxX, &maxY](auto &&line)
			{
				auto nums = std::ranges::to<std::vector<std::string>>(line | std::views::split(',')) | std::views::transform([](auto &&val) { return std::stoll(val); });
				auto it	  = nums.begin();

				auto res = Vector2<std::int64_t>{*it, *(++it)};

				maxX = std::max(maxX, res.x());
				maxY = std::max(maxY, res.y());

				return res;
			}));

	Grid<char> grid(maxX + 2, maxY + 2, '.');
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		auto start = tiles[i];
		auto end   = tiles[(i + 1) % tiles.size()];

		grid.set(start.x(), start.y(), '#');
		grid.set(end.x(), end.y(), '#');

		if (start.x() == end.x())
		{
			for (std::size_t y = std::min(start.y(), end.y()) + 1; y < std::max(start.y(), end.y()); ++y) { grid.set(start.x(), y, 'X'); }
		}
		else {
			for (std::size_t x = std::min(start.x(), end.x()) + 1; x < std::max(start.x(), end.x()); ++x) { grid.set(x, start.y(), 'X'); }
		}
	}

	for (const auto &row : grid.rows())
	{
		for (const auto &cell : row) { std::print("{}", cell); }
		std::println();
	}

	return "TODO: Solve";
}
