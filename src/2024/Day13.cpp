#include "2024/Day13.hpp"

#include <algorithm>
#include <ranges>
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
		a = {stoi(lines[0].substr(12, lines[0].find(" ", 13))), stoi(lines[0].substr(lines[0].find("Y") + 2))};
		b = {stoi(lines[1].substr(12, lines[1].find(" ", 13))), stoi(lines[1].substr(lines[1].find("Y") + 2))};
		prize = {stoi(lines[2].substr(9, lines[2].find(" ", 9))), stoi(lines[2].substr(lines[2].find("Y") + 2))};

		vector<long long> tokens;
		for (int i = 0; i < 100; i++)
		{
			Vector2<long long> movedA = a * i;
			Vector2<long long> movedB = b * i;
			Vector2<long long> remainingA = prize - movedA;
			Vector2<long long> remainingB = prize - movedB;

			if (remainingA.x() % b.x() == 0 && remainingA.y() % b.y() == 0)
			{
				if (a * i + b * (remainingA.x() / b.x()) == prize)
				{
					tokens.push_back(i * 3 + remainingA.x() / b.x());
				}
			}
			if (remainingB.x() % a.x() == 0 && remainingB.y() % a.y() == 0)
			{
				if (b * i + a * (remainingB.x() / a.x()) == prize)
				{
					tokens.push_back(i + remainingB.x() / a.x() * 3);
				}
			}
		}

		if (!tokens.empty())
		{
			sort(tokens.begin(), tokens.end());
			sum += tokens[0];
		}
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
		a = {stoi(lines[0].substr(12, lines[0].find(" ", 13))), stoi(lines[0].substr(lines[0].find("Y") + 2))};
		b = {stoi(lines[1].substr(12, lines[1].find(" ", 13))), stoi(lines[1].substr(lines[1].find("Y") + 2))};
		prize = {stoi(lines[2].substr(9, lines[2].find(" ", 9))), stoi(lines[2].substr(lines[2].find("Y") + 2))};
		prize.setX(prize.x() + offset);
		prize.setY(prize.y() + offset);

		// TODO: Create a line class, translate the Problem into two lines and calculate their intersection point.
		// Works on geogebra (y1 = 3x + ((Px-x*Ax)/(Bx)))
		//                   (y2 = 3x + ((Py-x*Ay)/(By)))
	}

	return to_string(sum);
}
