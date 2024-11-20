#include "2016/Day01.hpp"

#include <set>
#include <string>

Day01_2016::Day01_2016() { exampleInput = "R8, R4, R4, R8"; }

enum class Direction
{
	North,
	West,
	South,
	East
};

string Day01_2016::part1(const string& input, bool example)
{
	pair<int, int> position = {0, 0};
	Direction facing = Direction::North;

	size_t prevpos = 0, pos = input.find(',');
	for (;;)
	{
		char turn = input[prevpos];
		int steps = stoi(input.substr(prevpos + 1, pos - prevpos - 1));

		facing = static_cast<Direction>((static_cast<int>(facing) + (turn == 'L' ? 1 : -1) + 4) % 4);
		switch (facing)
		{
			case Direction::North:
				position.second += steps;
				break;
			case Direction::South:
				position.second -= steps;
				break;
			case Direction::East:
				position.first += steps;
				break;
			case Direction::West:
				position.first -= steps;
				break;
		}

		if (pos == string::npos) break;

		prevpos = pos + 2;
		pos = input.find(',', prevpos);
	}

	int distance = abs(position.first) + abs(position.second);

	return to_string(distance);
}

string Day01_2016::part2(const string& input, bool example)
{
	set<pair<int, int>> visited;

	pair<int, int> position = {0, 0};
	Direction facing = Direction::North;
	int distance = -1;

	size_t prevpos = 0, pos = input.find(',');
	for (;;)
	{
		char turn = input[prevpos];
		int steps = stoi(input.substr(prevpos + 1, pos - prevpos - 1));
    auto move = [&position, example, &facing, &visited](int steps, auto& move) -> int {
      if (steps == 0) return -1;

      switch (facing)
      {
        case Direction::North:
          position.second++;
          break;
        case Direction::South:
          position.second--;
          break;
        case Direction::East:
          position.first++;
          break;
        case Direction::West:
          position.first--;
          break;
      }

      if (visited.contains(position))
      {
        return abs(position.first) + abs(position.second);
      }
      else
      {
        visited.insert(position);
        return move(steps - 1, move);
      }
    };

		facing = static_cast<Direction>((static_cast<int>(facing) + (turn == 'L' ? 1 : -1) + 4) % 4);
    distance = move(steps, move);

		if (distance != -1 || pos == string::npos) break;

		prevpos = pos + 2;
		pos = input.find(',', prevpos);
	}

	if (distance == -1) return "No loop found";
	return to_string(distance);
}
