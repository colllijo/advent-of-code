#include "2024/Day08.hpp"

#include <set>
#include <unordered_map>
#include <utility>

#include "coll-aoc-runner/structs/Grid.hpp"

Day08_2024::Day08_2024()
{
	exampleInput =
	    "............\n"
	    "........0...\n"
	    ".....0......\n"
	    ".......0....\n"
	    "....0.......\n"
	    "......A.....\n"
	    "............\n"
	    "............\n"
	    "........A...\n"
	    ".........A..\n"
	    "............\n"
	    "............";
}

string Day08_2024::part1(const string& input, bool example)
{
	caoc::structs::Grid<char> grid(input);
	unordered_map<char, vector<pair<int, int>>> antennas;
	set<pair<int, int>> antinodes;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) != '.')
			{
				if (antennas.find(grid.get(x, y)) == antennas.end())
				{
					antennas[grid.get(x, y)] = { make_pair(x, y) };
				}
				else
				{
					antennas[grid.get(x, y)].push_back(make_pair(x, y));
				}
			}
		}
	}

	for (const auto& [freq, pos] : antennas)
	{
		for (int i = 0; i < pos.size() - 1; i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				int dx = pos[j].first - pos[i].first;
				int dy = pos[j].second - pos[i].second;
				if (grid.inBounds(pos[j].first + dx, pos[j].second + dy))
				{
					antinodes.insert(make_pair(pos[j].first + dx, pos[j].second + dy));
				}
				if (grid.inBounds(pos[i].first - dx, pos[i].second - dy))
				{
					antinodes.insert(make_pair(pos[i].first - dx, pos[i].second - dy));
				}
			}
		}
	}

	return to_string(antinodes.size());
}

string Day08_2024::part2(const string& input, bool example)
{
	caoc::structs::Grid<char> grid(input);
	unordered_map<char, vector<pair<int, int>>> antennas;
	set<pair<int, int>> antinodes;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) != '.')
			{
				if (antennas.find(grid.get(x, y)) == antennas.end())
				{
					antennas[grid.get(x, y)] = { make_pair(x, y) };
				}
				else
				{
					antennas[grid.get(x, y)].push_back(make_pair(x, y));
				}
			}
		}
	}

	for (const auto& [freq, pos] : antennas)
	{
		for (int i = 0; i < pos.size() - 1; i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				int dx = pos[j].first - pos[i].first;
				int dy = pos[j].second - pos[i].second;
				
				int mult = 0;
				while (grid.inBounds(pos[j].first + dx * mult, pos[j].second + dy * mult))
				{
					antinodes.insert(make_pair(pos[j].first + dx * mult, pos[j].second + dy * mult));
					mult++;
				}
				mult = 0;
				while (grid.inBounds(pos[j].first + dx * mult, pos[j].second + dy * mult))
				{
					antinodes.insert(make_pair(pos[j].first + dx * mult, pos[j].second + dy * mult));
					mult--;
				}
			}
		}
	}

	return to_string(antinodes.size());
}
