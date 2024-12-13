#include "2024/Day13.hpp"

#include <algorithm>
#include <vector>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace caoc;
using namespace caoc::structs;

Day13_2024::Day13_2024()
{
	exampleInput =
	    "Button A: X+94, Y+34\n"
	    "Button B: X+22, Y+67\n"
	    "Prize: X=8400, Y=5400\n"
	    "\n"
	    "Button A: X+26, Y+66\n"
	    "Button B: X+67, Y+21\n"
	    "Prize: X=12748, Y=12176\n"
	    "\n"
	    "Button A: X+17, Y+86\n"
	    "Button B: X+84, Y+37\n"
	    "Prize: X=7870, Y=6450\n"
	    "\n"
	    "Button A: X+69, Y+23\n"
	    "Button B: X+27, Y+71\n"
	    "Prize: X=18641, Y=10279";
}

string Day13_2024::part1(const string& input, bool example)
{
	long long sum = 0;
	for (const auto& machine : strings::split(input, "\n\n"))
	{
		auto lines = strings::split(machine, "\n");

		Vector2<long long> a, b, prize;
		a = {stoll(lines[0].substr(12, lines[0].find(" ", 13))), stoll(lines[0].substr(lines[0].find("Y") + 2))};
		b = {stoll(lines[1].substr(12, lines[1].find(" ", 13))), stoll(lines[1].substr(lines[1].find("Y") + 2))};
		prize = {stoll(lines[2].substr(9, lines[2].find(" ", 9))), stoll(lines[2].substr(lines[2].find("Y") + 2))};


    long long aPresses = (prize.y() * a.x() - prize.x() * a.y()) / (b.y() * a.x() - a.y() * b.x());
    long long bPresses = (prize.x() - b.x() * aPresses) / a.x();

    if (a * bPresses + b * aPresses == prize)
      sum += bPresses * 3 + aPresses;
	}

	return to_string(sum);
}

string Day13_2024::part2(const string& input, bool example)
{
	long long sum = 0;
	for (const auto& machine : strings::split(input, "\n\n"))
	{
		auto lines = strings::split(machine, "\n");

		long long offset = 10000000000000LL;

		Vector2<long long> a, b, prize;
		a = {stoll(lines[0].substr(12, lines[0].find(" ", 13))), stoll(lines[0].substr(lines[0].find("Y") + 2))};
		b = {stoll(lines[1].substr(12, lines[1].find(" ", 13))), stoll(lines[1].substr(lines[1].find("Y") + 2))};
		prize = {stoll(lines[2].substr(9, lines[2].find(" ", 9))), stoll(lines[2].substr(lines[2].find("Y") + 2))};
		prize.setX(prize.x() + offset);
		prize.setY(prize.y() + offset);

    long long aPresses = (prize.y() * a.x() - prize.x() * a.y()) / (b.y() * a.x() - a.y() * b.x());
    long long bPresses = (prize.x() - b.x() * aPresses) / a.x();

    if (a * bPresses + b * aPresses == prize)
      sum += bPresses * 3 + aPresses;
	}

	return to_string(sum);
}
