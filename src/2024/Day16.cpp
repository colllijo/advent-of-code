#include "2024/Day16.hpp"

#include <climits>
#include <functional>
#include <queue>

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

	using Pos = tuple<Vector2<int>, Direction>;
	using Node = tuple<uint64_t, Vector2<int>, Direction>;
	priority_queue<Node, vector<Node>, greater<Node>> queue;

	map<Pos, u_int64_t> dist;
	map<Pos, optional<Pos>> prev;

	dist[{start, startDir}] = 0;
	prev[{start, startDir}] = nullopt;

	queue.push({0, start, startDir});

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) != '#' && start != Vector2<int>{x, y})
			{
				for (const auto& dir : CardinalDirections)
				{
					dist[{{x, y}, dir}] = UINT64_MAX;
					prev[{{x, y}, dir}] = nullopt;
					queue.push({UINT64_MAX, {x, y}, dir});
				}
			}
		}
	}

	while (!queue.empty())
	{
		auto [cost, pos, dir] = queue.top();
		queue.pop();

		if (pos == end)
			return to_string(cost);

		if (grid.move(pos, dir) != '#')
		{
			if (cost + 1 < dist[{pos + dir.direction(), dir}])
			{
				prev[{pos + dir.direction(), dir}] = {pos, dir};
				dist[{pos + dir.direction(), dir}] = cost + 1;
				queue.push({cost + 1, pos + dir.direction(), dir});
			}
		}

		if (cost + 1000 < dist[{pos, Direction::rotateLeft(dir)}])
		{
			prev[{pos, Direction::rotateLeft(dir)}] = {pos, dir};
			dist[{pos, Direction::rotateLeft(dir)}] = cost + 1000;
			queue.push({cost + 1000, pos, Direction::rotateLeft(dir)});
		}

		if (cost + 1000 < dist[{pos, Direction::rotateRight(dir)}])
		{
			prev[{pos, Direction::rotateRight(dir)}] = {pos, dir};
			dist[{pos, Direction::rotateRight(dir)}] = cost + 1000;
			queue.push({cost + 1000, pos, Direction::rotateRight(dir)});
		}
	}

	return "End was not found";
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

	using Pos = tuple<Vector2<int>, Direction>;
	using Node = tuple<uint64_t, Vector2<int>, Direction>;
	priority_queue<Node, vector<Node>, greater<Node>> queue;

	map<Pos, u_int64_t> dist;
	map<Pos, vector<Pos>> prev;

	dist[{start, startDir}] = 0;
	prev[{start, startDir}] = {};

	queue.push({0, start, startDir});

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) != '#' && start != Vector2<int>{x, y})
			{
				for (const auto& dir : CardinalDirections)
				{
					dist[{{x, y}, dir}] = UINT64_MAX;
					prev[{{x, y}, dir}] = {};
					queue.push({UINT64_MAX, {x, y}, dir});
				}
			}
		}
	}

	Pos finalPos;
	while (!queue.empty())
	{
		auto [cost, pos, dir] = queue.top();
		queue.pop();

		if (pos == end)
		{
			finalPos = {pos, dir};
			break;
		}

		if (grid.move(pos, dir) != '#')
		{
			if (cost + 1 > cost && cost + 1 < dist[{pos + dir.direction(), dir}])
			{
				prev[{pos + dir.direction(), dir}] = {{pos, dir}};
				dist[{pos + dir.direction(), dir}] = cost + 1;
				queue.push({cost + 1, pos + dir.direction(), dir});
			}
			else if (cost + 1 > cost && cost + 1 == dist[{pos + dir.direction(), dir}])
			{
				prev[{pos + dir.direction(), dir}].push_back({pos, dir});
			}
		}

		if (cost + 1000 > cost && cost + 1000 < dist[{pos, Direction::rotateLeft(dir)}])
		{
			prev[{pos, Direction::rotateLeft(dir)}] = {{pos, dir}};
			dist[{pos, Direction::rotateLeft(dir)}] = cost + 1000;
			queue.push({cost + 1000, pos, Direction::rotateLeft(dir)});
		}
		else if (cost + 1000 > cost && cost + 1000 == dist[{pos, Direction::rotateLeft(dir)}])
		{
			prev[{pos, Direction::rotateLeft(dir)}].push_back({pos, dir});
		}

		if (cost + 1000 > cost && cost + 1000 < dist[{pos, Direction::rotateRight(dir)}])
		{
			prev[{pos, Direction::rotateRight(dir)}] = {{pos, dir}};
			dist[{pos, Direction::rotateRight(dir)}] = cost + 1000;
			queue.push({cost + 1000, pos, Direction::rotateRight(dir)});
		}
		else if (cost + 1000 > cost && cost + 1000 == dist[{pos, Direction::rotateRight(dir)}])
		{
			prev[{pos, Direction::rotateRight(dir)}].push_back({pos, dir});
		}
	}

	set<Vector2<int>> visited{get<0>(finalPos)};
	vector<Pos> path = prev[finalPos];

	while(!path.empty())
	{
		vector<Pos> steps;

		for (const auto& p : path)
		{
			visited.insert(get<0>(p));
			steps.insert(steps.end(), prev[p].begin(), prev[p].end());
		}

		path = steps;
	}

	return to_string(visited.size());
}
