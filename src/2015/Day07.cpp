#include "2015/Day07.hpp"

#include <algorithm>
#include <cwchar>
#include <sstream>
#include <string>
#include <unordered_map>
#include <regex>

Day07_2015::Day07_2015() {
  exampleInput =  "123 -> x\n456 -> y\nx AND y -> d\nx OR y -> e\nx LSHIFT 2 -> f\ny RSHIFT 2 -> g\nNOT x -> h\nNOT y -> i\n";
}

bool isNumeric (const string& str) {
  return std::all_of(str.begin(), str.end(), [](char c){ return std::isdigit(c); });
}

void solveWire(string name, unordered_map<string, string>& operations, unordered_map<string, unsigned short>& wires) {
  string operation = operations[name];
  string operand;
  unsigned short lValue, rValue;

  smatch match;
  if (regex_search(operation, match, regex(R"(^(NOT)? ?([0-9a-z]+$))"))) {
    if (isNumeric(match[2])) {
      lValue = stoi(match[2]);
    } else {
      if (!wires.contains(match[2])) solveWire(match[2], operations, wires);
      lValue = wires[match[2]];
    }

    if (match[1] == "NOT") {
      wires[name] = ~lValue;
    } else {
      wires[name] = lValue;
    }
  } else if (regex_search(operation, match, regex(R"(^([0-9a-z]+) (AND|OR|LSHIFT|RSHIFT) ([0-9a-z]+)$)"))) {
    if (isNumeric(match[1])) {
      lValue = stoi(match[1]);
    } else {
      if (!wires.contains(match[1])) solveWire(match[1], operations, wires);
      lValue = wires[match[1]];
    }

    if (isNumeric(match[3])) {
      rValue = stoi(match[3]);
    } else {
      if (!wires.contains(match[3])) solveWire(match[3], operations, wires);
      rValue = wires[match[3]];
    }

    if (match[2] == "AND") {
      wires[name] = lValue & rValue;
    } else if (match[2] == "OR") {
      wires[name] = lValue | rValue;
    } else if (match[2] == "LSHIFT") {
      wires[name] = lValue << rValue;
    } else if (match[2] == "RSHIFT") {
      wires[name] = lValue >> rValue;
    }
  }
}

string Day07_2015::part1(const string& input, bool example) {
  string target = example ? "d" : "a";

  unordered_map<string, string> operations;
  unordered_map<string, unsigned short> wires;

  stringstream stream(input); string instruction;
  while (getline(stream, instruction, '\n')) {
    int pos = instruction.find(" -> ");
    operations[instruction.substr(pos + 4)] =instruction.substr(0,  pos);
  }

  solveWire(target, operations, wires);

  return to_string(wires[target]);
}

string Day07_2015::part2(const string& input, bool example) {
  string target = example ? "d" : "a";

  unordered_map<string, string> operations;
  unordered_map<string, unsigned short> wires;

  wires["b"] = stoi(part1(input, example));

  stringstream stream(input); string instruction;
  while (getline(stream, instruction, '\n')) {
    int pos = instruction.find(" -> ");
    operations[instruction.substr(pos + 4)] =instruction.substr(0,  pos);
  }

  solveWire(target, operations, wires);

  return to_string(wires[target]);
}
