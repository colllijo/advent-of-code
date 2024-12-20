#include "2024/Day20.hpp"

#include <tuple>

#include "coll-aoc-runner/algorithms/Dijkstras.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"

Day20_2024::Day20_2024()
{
	exampleInput =
	    "###############\n"
	    "#...#...#.....#\n"
	    "#.#.#.#.#.###.#\n"
	    "#S#...#.#.#...#\n"
	    "#######.#.#.###\n"
	    "#######.#.#...#\n"
	    "#######.#.###.#\n"
	    "###..E#...#...#\n"
	    "###.#######.###\n"
	    "#...###...#...#\n"
	    "#.#####.#.###.#\n"
	    "#.#...#.#.#...#\n"
	    "#.#.#.#.#.#.###\n"
	    "#...#...#...###\n"
	    "###############";
}

string Day20_2024::part1(const string& input, bool example)
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
				start = {x, y};
			}
			else if (grid.get(x, y) == 'E')
			{
				end = {x, y};
			}
		}
	}

	auto [dist, prev] = algorithms::findBestPath<Vector2<int>>(start, end,
	    [&grid](const Vector2<int>& pos) -> vector<tuple<double, Vector2<int>>>
	    {
		    vector<tuple<double, Vector2<int>>> neighbors;

		    for (const auto& dir : CardinalDirections)
		    {
			    if (grid.inBounds(pos + dir.direction()) && grid.move(pos, dir) != '#')
			    {
				    neighbors.push_back({1, pos + dir.direction()});
			    }
		    }

		    return neighbors;
	    });

	vector<Vector2<int>> path;

	auto pos = optional<Vector2<int>>{end};
	do
	{
		path.emplace_back(pos.value());
		pos = prev[pos.value()];
	} while (pos.has_value());

	reverse(path.begin(), path.end());

	set<pair<Vector2<int>, Vector2<int>>> cuts{};
	for (int i = 0; i < path.size() - 1; i++)
	{
		for (int j = i + 1; j < path.size(); j++)
		{
			int distance = abs(path[i].x() - path[j].x()) + abs(path[i].y() - path[j].y());
			int save = j - i - distance;

			if (distance == 2 && save >= 100)
			{
				cuts.insert({path[i], path[j]});
			}
		}
	}

	return to_string(cuts.size());
}

string Day20_2024::part2(const string& input, bool example)
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
				start = {x, y};
			}
			else if (grid.get(x, y) == 'E')
			{
				end = {x, y};
			}
		}
	}

	auto [dist, prev] = algorithms::findBestPath<Vector2<int>>(start, end,
	    [&grid](const Vector2<int>& pos) -> vector<tuple<double, Vector2<int>>>
	    {
		    vector<tuple<double, Vector2<int>>> neighbors;

		    for (const auto& dir : CardinalDirections)
		    {
			    if (grid.inBounds(pos + dir.direction()) && grid.move(pos, dir) != '#')
			    {
				    neighbors.push_back({1, pos + dir.direction()});
			    }
		    }

		    return neighbors;
	    });

	vector<Vector2<int>> path;

	auto pos = optional<Vector2<int>>{end};
	do
	{
		path.emplace_back(pos.value());
		pos = prev[pos.value()];
	} while (pos.has_value());

	reverse(path.begin(), path.end());

	set<pair<Vector2<int>, Vector2<int>>> cuts{};
	for (int i = 0; i < path.size() - 1; i++)
	{
		for (int j = i + 1; j < path.size(); j++)
		{
			int distance = abs(path[i].x() - path[j].x()) + abs(path[i].y() - path[j].y());
			int save = j - i - distance;

			if (distance <= 20 && save >= 100)
			{
				cuts.insert({path[i], path[j]});
			}
		}
	}

	return to_string(cuts.size());
}
