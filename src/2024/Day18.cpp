#include "2024/Day18.hpp"

#include <bits/ranges_algo.h>

#include <functional>
#include <queue>

Day18_2024::Day18_2024()
{
	exampleInput =
	    "5,4\n"
	    "4,2\n"
	    "4,5\n"
	    "3,0\n"
	    "2,1\n"
	    "6,3\n"
	    "2,4\n"
	    "1,5\n"
	    "0,6\n"
	    "3,3\n"
	    "2,6\n"
	    "5,1\n"
	    "1,2\n"
	    "5,5\n"
	    "2,5\n"
	    "6,5\n"
	    "1,4\n"
	    "0,4\n"
	    "6,4\n"
	    "1,1\n"
	    "6,1\n"
	    "1,0\n"
	    "0,5\n"
	    "1,6\n"
	    "2,0";
}

string Day18_2024::part1(const string& input, bool example)
{
	int size = example ? 7 : 71;

	Grid<char> grid(size, size, '.');

	vector<Vector2<int>> corruptions;
	for (const auto& line : strings::split(input, "\n")) corruptions.push_back({stoi(line.substr(0, line.find(','))), stoi(line.substr(line.find(',') + 1))});

	int corruption = example ? 12 : 1024;
	for (int i = 0; i < corruption; i++) grid.set(corruptions[i], '#');

	Vector2<int> start{0, 0};
	Vector2<int> end{size - 1, size - 1};

	using Node = tuple<uint64_t, Vector2<int>>;
	priority_queue<Node, vector<Node>, greater<Node>> queue;

	map<Vector2<int>, u_int64_t> dist;
	map<Vector2<int>, optional<Vector2<int>>> prev;

	dist[start] = 0;
	prev[start] = nullopt;

	queue.push({0, start});

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) != '#' && start != Vector2<int>{x, y})
			{
				dist[{x, y}] = UINT64_MAX;
				prev[{x, y}] = nullopt;
				queue.push({UINT64_MAX, {x, y}});
			}
		}
	}

	while (!queue.empty())
	{
		auto [cost, pos] = queue.top();
		queue.pop();

		if (pos == end) return to_string(cost);

		for (const auto& dir : CardinalDirections)
		{
			if (grid.inBounds(pos + dir.direction()) && grid.move(pos, dir) != '#')
			{
				if (cost + 1 < dist[pos + dir.direction()])
				{
					prev[pos + dir.direction()] = pos;
					dist[pos + dir.direction()] = cost + 1;
					queue.push({cost + 1, pos + dir.direction()});
				}
			}
		}
	}

	return "TODO: Solve part 1.";
}

string Day18_2024::part2(const string& input, bool example)
{
	int size = example ? 7 : 71;

	Grid<char> grid(size, size, '.');

	vector<Vector2<int>> corruptions;
	for (const auto& line : strings::split(input, "\n")) corruptions.push_back({stoi(line.substr(0, line.find(','))), stoi(line.substr(line.find(',') + 1))});

	int corruption = example ? 12 : 1024;
	for (int i = 0; i < corruption; i++)
	{
		auto cor = *corruptions.begin();
		corruptions.erase(corruptions.begin());

		grid.set(cor, '#');
	}

	auto isPossible = [&size](const Grid<char>& grid) -> bool
	{
		Vector2<int> start{0, 0};
		Vector2<int> end{size - 1, size - 1};

		using Node = tuple<uint64_t, Vector2<int>>;
		priority_queue<Node, vector<Node>, greater<Node>> queue;

		map<Vector2<int>, u_int64_t> dist;
		map<Vector2<int>, optional<Vector2<int>>> prev;

		dist[start] = 0;
		prev[start] = nullopt;

		queue.push({0, start});

		for (int y = 0; y < grid.height(); y++)
		{
			for (int x = 0; x < grid.width(); x++)
			{
				if (grid.get(x, y) != '#' && start != Vector2<int>{x, y})
				{
					dist[{x, y}] = UINT64_MAX;
					prev[{x, y}] = nullopt;
					queue.push({UINT64_MAX, {x, y}});
				}
			}
		}

		while (!queue.empty())
		{
			auto [cost, pos] = queue.top();
			queue.pop();

			for (const auto& dir : CardinalDirections)
			{
				if (grid.inBounds(pos + dir.direction()) && grid.move(pos, dir) != '#')
				{
					if (cost + 1 > cost && cost + 1 < dist[pos + dir.direction()])
					{
						prev[pos + dir.direction()] = pos;
						dist[pos + dir.direction()] = cost + 1;
						queue.push({cost + 1, pos + dir.direction()});
					}
				}
			}
		}

		return dist[end] != UINT64_MAX;
	};

	auto getGrid = [&grid](const vector<Vector2<int>>& data, int index)
	{
		auto modified = grid;

		for (int i = 0; i <= index; i++) modified.set(data[i], '#');

		return modified;
	};

	auto binary_search = [&isPossible, &getGrid](const vector<Vector2<int>>& data)
	{
		int left = 0;
		int right = data.size() - 1;
		int pivot = -1;

		while (left <= right)
		{
			int mid = left + (right - left) / 2;

			if (isPossible(getGrid(data, mid)))
			{
				left = mid + 1;
			}
			else
			{
				pivot = mid;
				right = mid - 1;
			}
		}

		return pivot;
	};

	int bad = binary_search(corruptions);
	if (bad != -1) return "" + to_string(corruptions[bad].x()) + "," + to_string(corruptions[bad].y());

	return "Impossibility not found";
}
