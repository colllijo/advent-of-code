#include "2015/Day03.hpp"

#include <set>
#include <utility>

Day03_2015::Day03_2015() {
  exampleInput = "^>v<";
}

string Day03_2015::part1(const string& input, bool example) {
  int x = 0, y = 0;
  set<pair<int, int>> houses {{x, y}};

  for (auto c : input) {
    switch (c) {
      case '^': y++; break;
      case 'v': y--; break;
      case '>': x++; break;
      case '<': x--; break;
    }
    houses.insert({x, y});
  }

  return to_string(houses.size());
}

string Day03_2015::part2(const string& input, bool example) {
  int santaX = 0, santaY = 0;
  int roboX = 0, roboY = 0;
  set<pair<int, int>> houses {{santaX, santaY}};

  for (int i = 0; i < input.size(); i++) {
    int& x = i % 2 == 0 ? santaX : roboX;
    int& y = i % 2 == 0 ? santaY : roboY;

    switch (input[i]) {
      case '^': y++; break;
      case 'v': y--; break;
      case '>': x++; break;
      case '<': x--; break;
    }

    houses.insert({x, y});
  }

  return to_string(houses.size());
}
