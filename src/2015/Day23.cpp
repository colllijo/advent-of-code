#include "2015/Day23.hpp"

#include <map>
#include <regex>
#include <sstream>
#include <vector>

Day23_2015::Day23_2015()
{
	exampleInput =
	    "inc a\n"
	    "jio a, +2\n"
	    "tpl a\n"
	    "inc a\n";
}

struct Instruction
{
	string command;
	string registerName;
	int offset;
};

string Day23_2015::part1(const string& input, bool example)
{
	int instructionOffset = 0;
	vector<Instruction> instructions;
	map<string, unsigned long> regs{{"a", 0}, {"b", 0}};

	stringstream stream(input);
	string line;
	while (getline(stream, line, '\n'))
	{
		Instruction instruction{"", "", 0};
		smatch match;

		if (regex_search(line, match, regex("^(jie|jio) (\\w+), ([-+]?\\d+)$")))
		{
			instruction.command = match[1];
			instruction.registerName = match[2];
			instruction.offset = stoi(match[3]);
		}
		else if (regex_search(line, match, regex("^(jmp) ([-+]?\\d+)$")))
		{
			instruction.command = match[1];
			instruction.offset = stoi(match[2]);
		}
		else if (regex_search(line, match, regex("^(hlf|tpl|inc) (\\w+)$")))
		{
			instruction.command = match[1];
			instruction.registerName = match[2];
		}

		instructions.push_back(instruction);
	}

	while (instructionOffset < instructions.size())
	{
		auto [cmd, reg, off] = instructions[instructionOffset];

		if (cmd == "hlf")
			regs[reg] /= 2;
		else if (cmd == "tpl")
			regs[reg] *= 3;
		else if (cmd == "inc")
			regs[reg]++;
		else if (cmd == "jmp")
			instructionOffset += off - 1;
		else if (cmd == "jie" && (regs[reg] & 0b1) == 0)
			instructionOffset += off - 1;
		else if (cmd == "jio" && regs[reg] == 1)
			instructionOffset += off - 1;

		instructionOffset++;
	}

	return to_string(regs["b"]);
}

string Day23_2015::part2(const string& input, bool example)
{
	int instructionOffset = 0;
	vector<Instruction> instructions;
	map<string, unsigned long> regs{{"a", 1}, {"b", 0}};

	stringstream stream(input);
	string line;
	while (getline(stream, line, '\n'))
	{
		Instruction instruction{"", "", 0};
		smatch match;

		if (regex_search(line, match, regex("^(jie|jio) (\\w+), ([-+]?\\d+)$")))
		{
			instruction.command = match[1];
			instruction.registerName = match[2];
			instruction.offset = stoi(match[3]);
		}
		else if (regex_search(line, match, regex("^(jmp) ([-+]?\\d+)$")))
		{
			instruction.command = match[1];
			instruction.offset = stoi(match[2]);
		}
		else if (regex_search(line, match, regex("^(hlf|tpl|inc) (\\w+)$")))
		{
			instruction.command = match[1];
			instruction.registerName = match[2];
		}

		instructions.push_back(instruction);
	}

	while (instructionOffset < instructions.size())
	{
		auto [cmd, reg, off] = instructions[instructionOffset];

		if (cmd == "hlf")
			regs[reg] /= 2;
		else if (cmd == "tpl")
			regs[reg] *= 3;
		else if (cmd == "inc")
			regs[reg]++;
		else if (cmd == "jmp")
			instructionOffset += off - 1;
		else if (cmd == "jie" && (regs[reg] & 0b1) == 0)
			instructionOffset += off - 1;
		else if (cmd == "jio" && regs[reg] == 1)
			instructionOffset += off - 1;

		instructionOffset++;
	}

	return to_string(regs["b"]);
}
