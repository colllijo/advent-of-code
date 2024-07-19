#include "2015/Day05.hpp"

#include <regex>
#include <sstream>

Day05_2015::Day05_2015() {
  exampleInput = "ugknbfddgicrmopn\naaa\njchzalrnumimnmhp\nhaegwjzuvuyypxyu\ndvszwmarrgswjxmb";
}

string Day05_2015::part1(const string& input, bool example) {
  int count = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    if (regex_search(line, regex(R"(^(?=.*(\w)\1)(?=.*([aeiou].*){3,})(?!.*?ab|.*?cd|.*?pq|.*?xy).*$)"))) count++;
  }

  return to_string(count);
}

string Day05_2015::part2(const string& input, bool example) {
  int count = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    if (regex_search(line, regex(R"(^(?=.*(\w\w).*\1)(?=.*(\w).\2.*).*$)"))) count++;
  }

  return to_string(count);
}
