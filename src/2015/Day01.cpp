#include "2015/Day01.hpp"

Day01_2015::Day01_2015() {
  exampleInput = ")())())";
}

string Day01_2015::part1(const string& input, bool example) {
  int floor = 0;

  for (const char c : input) {
    if (c == '(') {
      floor++;
    } else if (c == ')') {
      floor--;
    }
  }

  return to_string(floor);
}

string Day01_2015::part2(const string& input, bool example) {
  int step = 0;
  int floor = 0;

  for (const char c : input) {
    step++;

    if (c == '(') {
      floor++;
    } else if (c == ')') {
      floor--;
    }

    if (floor == -1) return to_string(step);
  }

  return "NOT FOUND";
}
