#include "2015/Day10.hpp"
#include <cwchar>

Day10_2015::Day10_2015() {
  exampleInput = "";
}

string lookAndSay(const string &str) {
  string result;

  char instance;
  int count = 0;

  for (const auto &c : str) {
    if (c != instance) {
      if (count != 0) result += to_string(count) + instance;
      instance = c; count = 1;
    } else {
      count++;
    }
  }

  return result + to_string(count) + instance;
}

string Day10_2015::part1(const string& input, bool example) {
  string result = input;

  for (int i = 0; i < 40; i++)
    result = lookAndSay(result);

  return to_string(result.size());
}

string Day10_2015::part2(const string& input, bool example) {
  string result = input;

  for (int i = 0; i < 50; i++)
    result = lookAndSay(result);

  return to_string(result.size());
}
