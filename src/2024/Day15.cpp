#include "2024/Day15.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace caoc;
using namespace caoc::structs;

Day15_2024::Day15_2024()
{
	exampleInput =
	    "##########\n"
	    "#..O..O.O#\n"
	    "#......O.#\n"
	    "#.OO..O.O#\n"
	    "#..O@..O.#\n"
	    "#O#..O...#\n"
	    "#O..O..O.#\n"
	    "#.OO.O.OO#\n"
	    "#....O...#\n"
	    "##########\n"
	    "\n"
	    "<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^\n"
	    "vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v\n"
	    "><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<\n"
	    "<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^\n"
	    "^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><\n"
	    "^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^\n"
	    ">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^\n"
	    "<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>\n"
	    "^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>\n"
	    "v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^";
	// "#######\n"
	// "#...#.#\n"
	// "#.....#\n"
	// "#..OO@#\n"
	// "#..O..#\n"
	// "#.....#\n"
	// "#######\n"
	// "\n"
	// "<vv<<^^<<^^";
}

string Day15_2024::part1(const string& input, bool example)
{
	Grid<char> grid(strings::split(input, "\n\n")[0]);
	string moves = strings::split(input, "\n\n")[1];

	Vector2<int> pos;

	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == '@')
			{
				pos = {x, y};
				goto solve;
			}
		}
	}

solve:
	Direction dir;
	for (const char& move : moves)
	{
		switch (move)
		{
			case '^':
				dir = Direction::NORTH;
				break;
			case '>':
				dir = Direction::EAST;
				break;
			case 'v':
				dir = Direction::SOUTH;
				break;
			case '<':
				dir = Direction::WEST;
				break;
			default:
				continue;
		}

		if (grid.move(pos, dir) == '.')
		{
			grid.set(pos, '.');
			pos += dir.direction();
			grid.set(pos, '@');
		}
		else if (grid.move(pos, dir) == 'O')
		{
			int scalar = 2;
			while (grid.move(pos, dir, scalar) == 'O')
			{
				scalar++;
			}

			if (grid.move(pos, dir, scalar) == '.')
			{
				while (scalar > 1)
				{
					grid.set(pos + dir.direction() * (scalar - 1), '.');
					grid.set(pos + dir.direction() * scalar, 'O');
					scalar--;
				}

				grid.set(pos, '.');
				pos += dir.direction();
				grid.set(pos, '@');
			}
		}
	}

	long long sum = 0;
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == 'O')
			{
				sum += x + 100 * y;
			}
		}
	}

	return to_string(sum);
}

string Day15_2024::part2(const string& input, bool example)
{
	Grid<char> inputGrid(strings::split(input, "\n\n")[0]);
	string moves = strings::split(input, "\n\n")[1];

	Grid<char> grid(inputGrid.width() * 2, inputGrid.height(), '.');
	Vector2<int> pos;

	for (int y = 0; y < inputGrid.height(); y++)
	{
		for (int x = 0; x < inputGrid.width(); x++)
		{
			if (inputGrid.get(x, y) == '#')
			{
				grid.set(x * 2, y, inputGrid.get(x, y));
				grid.set(x * 2 + 1, y, inputGrid.get(x, y));
			}
			else if (inputGrid.get(x, y) == 'O')
			{
				grid.set(x * 2, y, '[');
				grid.set(x * 2 + 1, y, ']');
			}
			else if (inputGrid.get(x, y) == '@')
			{
				grid.set(x * 2, y, '@');
				pos = {x * 2, y};
			}
		}
	}

	int moveCount = 1;
	Direction dir;
	for (const char& move : moves)
	{
		switch (move)
		{
			case '^':
				dir = Direction::NORTH;
				break;
			case '>':
				dir = Direction::EAST;
				break;
			case 'v':
				dir = Direction::SOUTH;
				break;
			case '<':
				dir = Direction::WEST;
				break;
			default:
				continue;
		}

		if (grid.move(pos, dir) == '.')
		{
			grid.set(pos, '.');
			pos += dir.direction();
			grid.set(pos, '@');
		}
		else if (grid.move(pos, dir) == '[' || grid.move(pos, dir) == ']')
		{
			if (dir == static_cast<Direction>(Direction::WEST) || dir == static_cast<Direction>(Direction::EAST))
			{
				int scalar = 2;
				while (grid.move(pos, dir, scalar) == '[' || grid.move(pos, dir, scalar) == ']')
				{
					scalar++;
				}

				if (grid.move(pos, dir, scalar) == '.')
				{
					while (scalar > 1)
					{
						grid.set(pos + dir.direction() * scalar, grid.get(pos + dir.direction() * (scalar - 1)));
						grid.set(pos + dir.direction() * (scalar - 1), '.');
						scalar--;
					}

					grid.set(pos, '.');
					pos += dir.direction();
					grid.set(pos, '@');
				}
			}
			else
			{
				bool moveable = true;
				vector<pair<char, Vector2<int>>> toMove;

				vector<Vector2<int>> frontline{pos};

				while (!frontline.empty() && moveable)
				{
					vector<Vector2<int>> advances;

					for (const auto& front : frontline)
					{
						toMove.push_back({grid.get(front), front});

						if (grid.move(front, dir) == '[')
						{
							advances.push_back(front + dir.direction());
							advances.push_back(front + dir.direction() + static_cast<Direction>(Direction::EAST).direction());
						}
						else if (grid.move(front, dir) == ']')
						{
							advances.push_back(front + dir.direction());
							advances.push_back(front + dir.direction() + static_cast<Direction>(Direction::WEST).direction());
						}
						else if (grid.move(front, dir) == '#')
						{
							moveable = false;
						}
					}

					frontline = advances;
				}

				if (moveable)
				{
					for (const auto& move : toMove)
					{
						grid.set(move.second, '.');
					}

					for (const auto& move : toMove)
					{
						// if (example && moveCount == 22) printf("Move at %d, %d: %c\n", move.second.x(), move.second.y(), move.first);
						grid.set(move.second + dir.direction(), move.first);
					}

					pos += dir.direction();
				}
			}
		}
	}

	long long sum = 0;
	for (int y = 0; y < grid.height(); y++)
	{
		for (int x = 0; x < grid.width(); x++)
		{
			if (grid.get(x, y) == '[')
			{
				sum += x + 100 * y;
			}
		}
	}

	return to_string(sum);
}
