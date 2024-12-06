#include "2024/Day06.hpp"

#include <cstdio>
#include <future>
#include <numeric>
#include <set>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include "coll-aoc-runner/parallelism/ThreadPool.hpp"
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

Direction turnRight(Direction dir)
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
			return dir;
	}
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
	try
	{
		for (;;)
		{
			visited.insert(position);
			int magnitude = 0;
			while (grid.move(position.first, position.second, dir, magnitude + 1) != '#')
			{
				magnitude++;
				visited.insert({position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude});
			}

			position = {position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude};
			dir = turnRight(dir);
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(visited.size());
}

string Day06_2024::part2(const string& input, bool example)
{
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
	caoc::parallelism::ThreadPool pool;
	std::vector<std::future<bool>> loopSearches{};
	set<pair<int, int>> visited{position};

	try
	{
		for (;;)
		{
			int magnitude = 0;
			while (grid.move(position.first, position.second, dir, magnitude + 1) != '#')
			{
        magnitude++;
				if (visited.find({position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude}) == visited.end())
				{
          visited.insert({position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude});
					loopSearches.emplace_back(pool.enqueue(
					    [](const Grid<char> grid, const pair<int, int> position, int magnitude, const Direction dir) -> bool
					    {
						    auto positionCopy = position;
                Direction dirCopy = dir;

						    auto gridCopy = grid;
						    gridCopy.set(position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude, '#');

						    set<tuple<int, int, Direction>> visited{};
						    try
						    {
							    for (;;)
							    {
								    if (visited.find({positionCopy.first, positionCopy.second, dirCopy}) != visited.end())
								    {
									    return true;
								    }
								    visited.insert({positionCopy.first, positionCopy.second, dirCopy});

								    int magnitudeCopy = 0;
								    while (gridCopy.move(positionCopy.first, positionCopy.second, dirCopy, magnitudeCopy + 1) != '#') magnitudeCopy++;
								    positionCopy = {positionCopy.first + dirCopy.direction().first * magnitudeCopy,
								                    positionCopy.second + dirCopy.direction().second * magnitudeCopy};
								    dirCopy = turnRight(dirCopy);
							    }
						    }
						    catch (const exception& e)
						    {
							    return false;
						    }
					    },
					    grid, position, magnitude, dir));
				}
			}

			position = {position.first + dir.direction().first * magnitude, position.second + dir.direction().second * magnitude};
			dir = turnRight(dir);
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(accumulate(loopSearches.begin(), loopSearches.end(), 0, [](int acc, auto& search) { return acc + search.get(); }));
}
