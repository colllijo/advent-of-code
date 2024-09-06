#include "2015/Day16.hpp"
#include <functional>
#include <map>
#include <sstream>

Day16_2015::Day16_2015() {
  exampleInput = "";
}

string Day16_2015::part1(const string& input, bool example) {
  map<string, int> properties {
    { "children:", 3 },
    { "cats:", 7 },
    { "samoyeds:", 2 },
    { "pomeranians:", 3 },
    { "akitas:", 0 },
    { "vizslas:", 0 },
    { "goldfish:", 5 },
    { "trees:", 3 },
    { "cars:", 2 },
    { "perfumes:", 1 }
  };

  stringstream stream(input); string line;
  while (getline(stream, line)) {
    int num;
    char property1[16], property2[16], property3[16];
    int value1, value2, value3;

    sscanf(line.c_str(), "Sue %d: %15s %d, %15s %d, %15s %d", &num, property1, &value1, property2, &value2, property3, &value3);

    if (properties[property1] == value1 && properties[property2] == value2 && properties[property3] == value3)
      return to_string(num);
  }

  return "Could not find matching aunt.";
}

string Day16_2015::part2(const string& input, bool example) {
  map<string, function<bool(int)>> properties {
    { "children:", [](int v){ return v == 3; } },
    { "cats:", [](int v){ return v > 7; } },
    { "samoyeds:", [](int v){ return v == 2; } },
    { "pomeranians:", [](int v){ return v < 3; } },
    { "akitas:", [](int v){ return v == 0; } },
    { "vizslas:", [](int v){ return v == 0; } },
    { "goldfish:", [](int v){ return v < 5; } },
    { "trees:", [](int v){ return v > 3; } },
    { "cars:", [](int v){ return v == 2; } },
    { "perfumes:", [](int v){ return v == 1; } }
  };

  stringstream stream(input); string line;
  while (getline(stream, line)) {
    int num;
    char property1[16], property2[16], property3[16];
    int value1, value2, value3;

    sscanf(line.c_str(), "Sue %d: %15s %d, %15s %d, %15s %d", &num, property1, &value1, property2, &value2, property3, &value3);

    if (properties[property1](value1) && properties[property2](value2) && properties[property3](value3))
      return to_string(num);
  }

  return "Could not find matching aunt.";
}
