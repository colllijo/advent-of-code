#include "2024/Day17.hpp"

#include <algorithm>
#include <cmath>

Day17_2024::Day17_2024()
{
	exampleInput =
	    // "Register A: 729\n"
	    // "Register B: 0\n"
	    // "Register C: 0\n"
	    // "\n"
	    // "Program: 0,1,5,4,3,0";
	    "Register A: 2024\n"
	    "Register B: 0\n"
	    "Register C: 0\n"
	    "\n"
	    "Program: 0,3,5,4,3,0";
}

string Day17_2024::part1(const string& input, bool example)
{
	string console = "";

	long regA = stol(strings::split(strings::split(input, "\n\n")[0], "\n")[0].substr(12));

	do
	{
		if (!console.empty()) console += ",";
		console += to_string(((((regA % 8) ^ 1) ^ (regA >> ((regA % 8) ^ 1))) ^ 4) % 8);
		regA /= 8;
	} while (regA != 0);

	return console;
}

string Day17_2024::part2(const string& input, bool example)
{
	string program = input.substr(input.find("Program: ") + 9);
	program.erase(std::remove(program.begin(), program.end(), ','), program.end());
	reverse(program.begin(), program.end());

	auto eval = [](long regA) -> string
	{
		string console = "";

		do
		{
			console += to_string(((((regA % 8) ^ 1) ^ (regA >> ((regA % 8) ^ 1))) ^ 4) % 8);
			regA /= 8;
		} while (regA != 0);

		reverse(console.begin(), console.end());
		return console;
	};

	vector<long> initial{0};
	for (int i = 1; i <= program.size(); i++)
	{
		vector<long> possible{};

		for (const auto& num : initial)
		{
			for (int offset = 0; offset < 8; offset++)
			{
				long a = num * 8 + offset;

				if (eval(a) == program.substr(0, i))
				{
					possible.push_back(a);
				}
			}
		}

		initial = possible;
	}

	sort(initial.begin(), initial.end());

	return to_string(initial[0]);
}
