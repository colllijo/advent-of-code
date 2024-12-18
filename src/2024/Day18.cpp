#include "2024/Day18.hpp"

#include <bits/ranges_algo.h>

#include <functional>

#include "coll-aoc-runner/algorithms/Dijkstras.hpp"

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

  auto [dist, _] = algorithms::findBestPath<Vector2<int>>(start, end, [&grid](const Vector2<int>& pos) -> vector<tuple<double, Vector2<int>>>
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

	return to_string(static_cast<int>(dist[end]));
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

  Vector2<int> start{0, 0};
  Vector2<int> end{size - 1, size - 1};

	auto getGrid = [&grid](const vector<Vector2<int>>& data, int index)
	{
		auto modified = grid;

		for (int i = 0; i <= index; i++) modified.set(data[i], '#');

		return modified;
	};

	auto binary_search = [&start, &end, &getGrid](const vector<Vector2<int>>& data)
	{
		int left = 0;
		int right = data.size() - 1;
		int pivot = -1;

		while (left <= right)
		{
			int mid = left + (right - left) / 2;

      const auto grid = getGrid(data, mid);
      auto [dist, _] = algorithms::findBestPath<Vector2<int>>(start, end, [&grid](const Vector2<int>& pos) -> vector<tuple<double, Vector2<int>>>
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


			if (dist.contains(end))
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
