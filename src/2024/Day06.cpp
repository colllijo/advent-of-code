#include "2024/Day06.hpp"

#include <set>
#include <tuple>
#include <utility>

#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"

using caoc::structs::Direction;
using caoc::structs::Grid;

Day06_2024::Day06_2024()
{
	exampleInput =
	    "....#.....\n"
	    ".........#\n"
	    "..........\n"
	    "..#.......\n"
	    ".......#..\n"
	    "..........\n"
	    ".#..^.....\n"
	    "........#.\n"
	    "#.........\n"
	    "......#...";
}

string Day06_2024::part1(const string& input, bool example)
{
	set<pair<int, int>> visited{};
	pair<int, int> position{0, 0};
	Grid<char> grid{input};
	Direction dir = Direction::NORTH;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == '^')
			{
				position = {x, y};
				goto solve;
			}
		}
	}
solve:

	auto turnRight = [](Direction dir)
	{
		switch (dir)
		{
			case Direction::NORTH:
				return Direction::EAST;
			case Direction::EAST:
				return Direction::SOUTH;
			case Direction::SOUTH:
				return Direction::WEST;
			case Direction::WEST:
				return Direction::NORTH;
      default:
        return static_cast<Direction::Value>(dir);
		}
	};

	visited.insert(position);
	try
	{
		for (;;)
		{
			if (grid.move(position.first, position.second, dir) != '#')
			{
				position = {position.first + dir.direction().first, position.second + dir.direction().second};
				visited.insert(position);
			}
			else
			{
				dir = turnRight(dir);
			}
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(visited.size());
}

string Day06_2024::part2(const string& input, bool example)
{
	set<pair<int, int>> positions{};
  set<tuple<int, int, Direction>> visited{};
	pair<int, int> position{0, 0};
	Grid<char> grid{input};
	Direction dir = Direction::NORTH;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == '^')
			{
				position = {x, y};
				goto solve;
			}
		}
	}
solve:

	auto turnRight = [](Direction dir)
	{
		switch (dir)
		{
			case Direction::NORTH:
				return Direction::EAST;
			case Direction::EAST:
				return Direction::SOUTH;
			case Direction::SOUTH:
				return Direction::WEST;
			case Direction::WEST:
				return Direction::NORTH;
      default:
        return static_cast<Direction::Value>(dir);
		}
	};
	auto isLoop = [&turnRight](Grid<char>& grid, pair<int, int> pos, auto& isLoop, Direction dir = Direction::NORTH, set<tuple<int, int, Direction>> visited = {}) -> bool
	{
		if (visited.find({pos.first, pos.second, dir}) != visited.end())
		{
			return true;
		}
		visited.insert({pos.first, pos.second, dir});
		try
		{
      int magnitude = 0;
      while (grid.move(pos.first, pos.second, dir, magnitude + 1) != '#') magnitude++;

      pos = {pos.first + dir.direction().first * magnitude, pos.second + dir.direction().second * magnitude};
      dir = turnRight(dir);
		}
		catch (const exception& e)
		{
			return false;
		}
		return isLoop(grid, pos, isLoop, dir, visited);
	};

	auto pathPos = position;
	long long loops = 0;
  int i = 0;
	try
	{
		for (;;)
		{
			if (grid.move(pathPos.first, pathPos.second, dir) != '#')
			{
				pathPos = {pathPos.first + dir.direction().first, pathPos.second + dir.direction().second};

        if (positions.find(pathPos) == positions.end())
        {
          auto changedGrid = grid;
          pair<int, int> changedPos = {pathPos.first - dir.direction().first, pathPos.second - dir.direction().second};
          auto changeVisited = visited;
          changedGrid.set(pathPos.first, pathPos.second, '#');

          if (isLoop(changedGrid, changedPos, isLoop, dir))
          {
            loops++;
          }
        }

				positions.insert(pathPos);
        visited.insert({pathPos.first, pathPos.second, dir});
			}
			else
			{
				dir = turnRight(dir);
			}
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(loops);
}
