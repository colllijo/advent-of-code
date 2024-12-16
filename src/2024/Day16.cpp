#include "2024/Day16.hpp"

#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace caoc::structs;

Day16_2024::Day16_2024()
{
	exampleInput =
	    "###############\n"
	    "#.......#....E#\n"
	    "#.#.###.#.###.#\n"
	    "#.....#.#...#.#\n"
	    "#.###.#####.#.#\n"
	    "#.#.#.......#.#\n"
	    "#.#.#####.###.#\n"
	    "#...........#.#\n"
	    "###.#.#####.#.#\n"
	    "#...#.....#.#.#\n"
	    "#.#.#.###.#.#.#\n"
	    "#.....#...#.#.#\n"
	    "#.###.#.#.#.#.#\n"
	    "#S..#.....#...#\n"
	    "###############";
}

string Day16_2024::part1(const string& input, bool example)
{
	Grid<char> grid(input);

	Vector2<int> start;
	Vector2<int> end;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == 'S')
			{
				start = Vector2<int>(x, y);
			}
			if (grid.get(x, y) == 'E')
			{
				end = Vector2<int>(x, y);
			}
		}
	}

	vector<long long> costs;
	map<pair<Vector2<int>, Direction>, long long> visited;
	set<tuple<Vector2<int>, Direction, long long>> frontline;

	frontline.insert(make_tuple(start, Direction::EAST, 0));
	while (!frontline.empty())
	{
		set<tuple<Vector2<int>, Direction, long long>> advances{};

		for (const auto& [position, dir, cost] : frontline)
		{
			if (visited.find({position, dir}) != visited.end() && visited[{position, dir}] <= cost)
			{
				continue;
			}
			visited[{position, dir}] = cost;

			if (position == end)
			{
				costs.push_back(cost);
				continue;
			}

			if (grid.move(position, dir) != '#')
			{
				advances.insert({position + dir.direction(), dir, cost + 1});
			}
			advances.insert({position, Direction::rotateLeft(dir), cost + 1000});
			advances.insert({position, Direction::rotateRight(dir), cost + 1000});
		}

		frontline = advances;
	}

	sort(costs.begin(), costs.end());

	return to_string(costs[0]);
}

string Day16_2024::part2(const string& input, bool example)
{
	Grid<char> grid(input);

	Vector2<int> start;
	Vector2<int> end;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == 'S')
			{
				start = Vector2<int>(x, y);
			}
			if (grid.get(x, y) == 'E')
			{
				end = Vector2<int>(x, y);
			}
		}
	}

	long long minCost = LLONG_MAX;
	map<pair<Vector2<int>, Direction>, long long> visited;
	set<tuple<Vector2<int>, Direction, long long, set<Vector2<int>>>> frontline;
	set<Vector2<int>> paths;

	frontline.insert(make_tuple(start, Direction::EAST, 0, set<Vector2<int>>{}));
	while (!frontline.empty())
	{
		set<tuple<Vector2<int>, Direction, long long, set<Vector2<int>>>> advances{};

		for (const auto& [position, dir, cost, path] : frontline)
		{
			if (visited.find({position, dir}) != visited.end() && visited[{position, dir}] < cost)
			{
				continue;
			}
			visited[{position, dir}] = cost;

			auto pathCopy = path;
			pathCopy.insert(position);

			if (position == end)
			{
				if (cost < minCost)
				{
					minCost = cost;
					paths.clear();
				}

				if (cost == minCost)
				{
					paths.insert(pathCopy.begin(), pathCopy.end());
				}
				continue;
			}

			if (grid.move(position, dir) != '#')
			{
				advances.insert({position + dir.direction(), dir, cost + 1, pathCopy});
			}
			advances.insert({position, Direction::rotateLeft(dir), cost + 1000, pathCopy});
			advances.insert({position, Direction::rotateRight(dir), cost + 1000, pathCopy});
		}

		frontline = advances;
	}


	return to_string(paths.size());
}
