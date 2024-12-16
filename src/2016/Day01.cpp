#include "2016/Day01.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

Day01_2016::Day01_2016() { exampleInput = "R8, R4, R4, R8"; }

string Day01_2016::part1(const string& input, bool example)
{
	Vector2<int> position = {0, 0};
	Direction facing = Direction::NORTH;

	size_t prevpos = 0, pos = input.find(',');
	for (;;)
	{
		char turn = input[prevpos];
		int steps = stoi(input.substr(prevpos + 1, pos - prevpos - 1));

    if (turn == 'L')
      facing.rotateLeft();
    else
      facing.rotateRight();

    position += facing.direction() * steps;

		if (pos == string::npos) break;

		prevpos = pos + 2;
		pos = input.find(',', prevpos);
	}

	int distance = abs(position.x()) + abs(position.y());

	return to_string(distance);
}

string Day01_2016::part2(const string& input, bool example)
{
	unordered_set<Vector2<int>> visited;

	Vector2<int> position = {0, 0};
	Direction facing = Direction::NORTH;
	int distance = -1;

	size_t prevpos = 0, pos = input.find(',');
	for (;;)
	{
		char turn = input[prevpos];
		int steps = stoi(input.substr(prevpos + 1, pos - prevpos - 1));

    auto move = [&position, example, &facing, &visited](int steps, auto& move) -> int {
      if (steps == 0) return -1;

      position += facing.direction();

      if (visited.contains(position))
      {
        return abs(position.x()) + abs(position.y());
      }
      else
      {
        visited.insert(position);
        return move(steps - 1, move);
      }
    };

    if (turn == 'L')
      facing.rotateLeft();
    else
      facing.rotateRight();

    distance = move(steps, move);

		if (distance != -1 || pos == string::npos) break;

		prevpos = pos + 2;
		pos = input.find(',', prevpos);
	}

	if (distance == -1) return "No loop found";
	return to_string(distance);
}
