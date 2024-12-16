#include "2024/Day06.hpp"

#include <cstdio>
#include <future>
#include <numeric>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "coll-aoc-runner/parallelism/ThreadPool.hpp"
#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace caoc::structs;

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
	unordered_set<Vector2<int>> visited{};
	Vector2<int> position{0, 0};
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
	int count = 0;
	try
	{
		for (;;)
		{
			visited.insert(position);
			int magnitude = 0;
			while (grid.move(position, dir, magnitude + 1) != '#')
			{
				++count;
				magnitude++;
				visited.insert(position + (dir.direction() * magnitude));
			}

			position += (dir.direction() * magnitude);
      dir.rotateRight();
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(visited.size());
}

string Day06_2024::part2(const string& input, bool example)
{
	Vector2<int> position{0, 0};
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
	unordered_set<Vector2<int>> visited{position};

	try
	{
		for (;;)
		{
			int magnitude = 0;
			while (grid.move(position, dir, magnitude + 1) != '#')
			{
				magnitude++;
				if (visited.find(position + (dir.direction() * magnitude)) == visited.end())
				{
					visited.insert(position + (dir.direction() * magnitude));
					loopSearches.emplace_back(pool.enqueue(
					    [](const Grid<char> grid, const Vector2<int> position, int magnitude, const Direction dir) -> bool
					    {
						    auto positionCopy = position;
						    Direction dirCopy = dir;

						    auto gridCopy = grid;
						    gridCopy.set(position + (dir.direction() * magnitude), '#');

						    set<tuple<Vector2<int>, Direction>> visited{};
						    try
						    {
							    for (;;)
							    {
								    if (visited.find({positionCopy, dirCopy}) != visited.end())
								    {
									    return true;
								    }
								    visited.insert({positionCopy, dirCopy});

								    int magnitudeCopy = 0;
								    while (gridCopy.move(positionCopy, dirCopy, magnitudeCopy + 1) != '#') magnitudeCopy++;
								    positionCopy += dirCopy.direction() * magnitudeCopy;
                    dirCopy.rotateRight();
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

			position += dir.direction() * magnitude;
      dir.rotateRight();
		}
	}
	catch (const exception& e)
	{
	}

	return to_string(accumulate(loopSearches.begin(), loopSearches.end(), 0, [](int acc, auto& search) { return acc + search.get(); }));
}
