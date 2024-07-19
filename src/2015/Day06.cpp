#include "2015/Day06.hpp"

#include <array>
#include <numeric>
#include <regex>
#include <sstream>

Day06_2015::Day06_2015() {
  exampleInput = "";
}

string Day06_2015::part1(const string& input, bool example) {
  array<array<bool, 1000>, 1000> grid {};

  stringstream stream(input); string instruction;
  while (getline(stream, instruction, '\n')) {
    smatch matches;
    if (regex_search(instruction, matches, regex(R"((turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+))"))) {
      int x1 = stoi(matches[2]), y1 = stoi(matches[3]);
      int x2 = stoi(matches[4]), y2 = stoi(matches[5]);
      for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
          if (matches[1] == "turn on") {
            grid[x][y] = true;
          } else if (matches[1] == "turn off") {
            grid[x][y] = false;
          } else if (matches[1] == "toggle") {
            grid[x][y] = !grid[x][y];
          }
        }
      }
    }
  }

  return to_string(
    accumulate(grid.begin(), grid.end(), 0, [](int sum, const array<bool, 1000>& row) {
      return sum + accumulate(row.begin(), row.end(), 0, [](int sum, bool light) {
        return sum + light;
      });
    })
  );
}

string Day06_2015::part2(const string& input, bool example) {
  array<array<int, 1000>, 1000> grid {};

  stringstream stream(input); string instruction;
  while (getline(stream, instruction, '\n')) {
    smatch matches;
    if (regex_search(instruction, matches, regex(R"((turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+))"))) {
      int x1 = stoi(matches[2]), y1 = stoi(matches[3]);
      int x2 = stoi(matches[4]), y2 = stoi(matches[5]);
      for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
          if (matches[1] == "turn on") {
            grid[x][y]++;
          } else if (matches[1] == "turn off") {
            grid[x][y] = max(grid[x][y] - 1, 0);
          } else if (matches[1] == "toggle") {
            grid[x][y] += 2;
          }
        }
      }
    }
  }

  return to_string(
    accumulate(grid.begin(), grid.end(), 0, [](int sum, const array<int, 1000>& row) {
      return sum + accumulate(row.begin(), row.end(), 0, [](int sum, int light) {
        return sum + light;
      });
    })
  );
}
