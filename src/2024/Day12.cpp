#include "2024/Day12.hpp"

#include <set>
#include <unordered_set>

#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

Day12_2024::Day12_2024()
{
	exampleInput =
	    "RRRRIICCFF\n"
	    "RRRRIICCCF\n"
	    "VVRRRCCFFF\n"
	    "VVRCCCJFFF\n"
	    "VVVVCJJCFE\n"
	    "VVIVCCJJEE\n"
	    "VVIIICJJEE\n"
	    "MIIIIIJJEE\n"
	    "MIIISIJEEE\n"
	    "MMMISSJEEE";
}

using namespace caoc::structs;

string Day12_2024::part1(const string& input, bool example)
{
	Grid<char> grid(input);
	unordered_set<Vector2<int>> visited;

	long long sum = 0;
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (visited.find({x, y}) != visited.end()) continue;

			char region = grid.get(x, y);

			long area = 0;
			long perimeter = 0;

			set<Vector2<int>> paths{{x, y}};

			while (!paths.empty())
			{
				set<Vector2<int>> newPaths;
				for (const auto& path : paths)
				{
					visited.insert(path);
					area++;
					for (const auto& dir : CardinalDirections)
					{
						auto newPath = path + dir.direction();
						if (grid.inBounds(newPath) && grid.get(newPath) == region)
						{
							if (visited.find(newPath) == visited.end())
							{
								newPaths.insert(newPath);
							}
						}
						else
						{
							perimeter++;
						}
					}
				}

				paths = newPaths;
			}

			sum += area * perimeter;
		}
	}

	return to_string(sum);
}

string Day12_2024::part2(const string& input, bool example)
{
	Grid<char> grid(input);
	unordered_set<Vector2<int>> visited;

	long long sum = 0;
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (visited.find({x, y}) != visited.end()) continue;

			char region = grid.get(x, y);

			long area = 0;

			Grid<char> patches(grid.width(), grid.height(), ' ');
			set<Vector2<int>> paths{{x, y}};

			while (!paths.empty())
			{
				set<Vector2<int>> newPaths;
				for (const auto& path : paths)
				{
					patches.set(path, '#');
					visited.insert(path);
					area++;
					for (const auto& dir : CardinalDirections)
					{
						auto newPath = path + dir.direction();
						if (grid.inBounds(newPath) && grid.get(newPath) == region)
						{
							if (visited.find(newPath) == visited.end())
							{
								newPaths.insert(newPath);
							}
						}
						else
						{
						}
					}
				}

				paths = newPaths;
			}

			int sides = 0;
			for (int y2 = 0; y2 < patches.height(); y2++)
			{
				bool top = false;
				bool bottom = false;
				for (int x2 = 0; x2 < patches.width(); x2++)
				{
					if (patches.get(x2, y2) == '#')
					{
						if (!patches.inBounds(x2, y2 - 1) || patches.get(x2, y2 - 1) == ' ')
						{
							top = true;
						}
						else if (top == true && patches.get(x2, y2 - 1) == '#')
						{
							sides++;
							top = false;
						}

						if (!patches.inBounds(x2, y2 + 1) || patches.get(x2, y2 + 1) == ' ')
						{
							bottom = true;
						}
						else if (bottom == true && patches.get(x2, y2 + 1) == '#')
						{
							sides++;
							bottom = false;
						}
					}
					else
					{
						sides += top + bottom;
						top = false;
						bottom = false;
					}
				}

				sides += top + bottom;
			}

			for (int x2 = 0; x2 < patches.width(); x2++)
			{
				bool left = false;
				bool right = false;
				for (int y2 = 0; y2 < patches.height(); y2++)
				{
					if (patches.get(x2, y2) == '#')
					{
						if (!patches.inBounds(x2 - 1, y2) || patches.get(x2 - 1, y2) == ' ')
						{
							left = true;
						}
						else if (left == true && patches.get(x2 - 1, y2) == '#')
						{
							sides++;
							left = false;
						}

						if (!patches.inBounds(x2 + 1, y2) || patches.get(x2 + 1, y2) == ' ')
						{
							right = true;
						}
						else if (right == true && patches.get(x2 + 1, y2) == '#')
						{
							sides++;
							right = false;
						}
					}
					else
					{
						sides += left + right;
						left = false;
						right = false;
					}
				}

				sides += left + right;
			}

			sum += area * sides;
		}
	}

	return to_string(sum);
}
