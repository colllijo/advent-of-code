#include "2024/Day16.hpp"

#include <algorithm>
#include <climits>
#include <functional>

#include "coll-aoc-runner/algorithms/Dijkstras.hpp"
#include "coll-aoc-runner/structs/Direction.hpp"

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
	Direction startDir = Direction::EAST;

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

  auto [dist, _] = algorithms::findBestPath<tuple<Vector2<int>, Direction>>({start, startDir}, [&grid](const tuple<Vector2<int>, Direction>& pos) -> vector<tuple<double, tuple<Vector2<int>, Direction>>>
  {
    vector<tuple<double, tuple<Vector2<int>, Direction>>> neighbors;

  if (grid.move(get<0>(pos), get<1>(pos)) != '#')
  {
      neighbors.push_back({1, {get<0>(pos) + get<1>(pos).direction(), get<1>(pos)}});
  }

    neighbors.push_back({1000, {get<0>(pos), Direction::rotateLeft(get<1>(pos))}});
    neighbors.push_back({1000, {get<0>(pos), Direction::rotateRight(get<1>(pos))}});

    return neighbors;
  });

  int minDist = INT_MAX;
  for (const auto& dir : CardinalDirections)
    minDist = min(minDist, static_cast<int>(dist[{end, dir}]));

  return to_string(minDist);
}

string Day16_2024::part2(const string& input, bool example)
{
	Grid<char> grid(input);

	Vector2<int> start;
	Vector2<int> end;
	Direction startDir = Direction::EAST;

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

  auto [dist, prev] = algorithms::findBestPaths<tuple<Vector2<int>, Direction>>({start, startDir}, [&grid](const tuple<Vector2<int>, Direction>& pos) -> vector<tuple<double, tuple<Vector2<int>, Direction>>>
  {
    vector<tuple<double, tuple<Vector2<int>, Direction>>> neighbors;

  if (grid.move(get<0>(pos), get<1>(pos)) != '#')
  {
      neighbors.push_back({1, {get<0>(pos) + get<1>(pos).direction(), get<1>(pos)}});
  }

    neighbors.push_back({1000, {get<0>(pos), Direction::rotateLeft(get<1>(pos))}});
    neighbors.push_back({1000, {get<0>(pos), Direction::rotateRight(get<1>(pos))}});

    return neighbors;
  });

  Direction endDir;
  int minDist = INT_MAX;
  for (const auto& dir : CardinalDirections)
  {
    if (static_cast<int>(dist[{end, dir}]) < minDist)
    {
      minDist = static_cast<int>(dist[{end, dir}]);
      endDir = dir;
    }
  }

	set<Vector2<int>> visited{end};
	vector<tuple<Vector2<int>, Direction>> path = prev[{end, endDir}];

	while(!path.empty())
	{
    vector<tuple<Vector2<int>, Direction>> steps;

		for (const auto& p : path)
		{
			visited.insert(get<0>(p));
			steps.insert(steps.end(), prev[p].begin(), prev[p].end());
		}

		path = steps;
	}

	return to_string(visited.size());
}
