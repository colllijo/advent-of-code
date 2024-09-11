#include "2015/Day18.hpp"
#include <array>
#include <cwchar>
#include <sstream>

Day18_2015::Day18_2015() {
  exampleInput = "";
}

int countSurrounding(int x, int y, const array<array<bool, 100>, 100> &grid) {
  int count = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      if (x + j < 0 || x + j >= 100 || y + i < 0 || y + i >= 100) continue;
      if (grid[y + i][x + j]) count++;
    }
  }

  return count;
}

string Day18_2015::part1(const string& input, bool example) {
  array<array<bool, 100>, 100> grid;
  array<array<bool, 100>, 100> tempGrid;

  int count = 0;
  stringstream stream(input); string line;
  while (getline(stream, line)) {
    for (int i = 0; i < line.size(); i++) {
      grid[count][i] = line[i] == '#';
    }
    count++;
  }

  for (int iter = 0; iter < 100; iter++) {
    for (int y = 0; y < 100; y++) {
      for (int x = 0; x < 100; x++) {
        int surrounding = countSurrounding(x, y, grid);
        if (grid[y][x]) {
          tempGrid[y][x] = surrounding == 2 || surrounding == 3;
        } else {
          tempGrid[y][x] = surrounding == 3;
        }
      }
    }
    grid = tempGrid;
  }

  auto countLights = [&]() {
    int count = 0;
    for (int y = 0; y < 100; y++) {
      for (int x = 0; x < 100; x++) {
        if (grid[y][x]) count++;
      }
    }
    return count;
  };

  return to_string(countLights());
}

string Day18_2015::part2(const string& input, bool example) {
  array<array<bool, 100>, 100> grid;
  array<array<bool, 100>, 100> tempGrid;

  int count = 0;
  stringstream stream(input); string line;
  while (getline(stream, line)) {
    for (int i = 0; i < line.size(); i++) {
      grid[count][i] = line[i] == '#';
    }
    count++;
  }

  // Corner lights are always on
  grid[0][0] = true;
  grid[0][99] = true;
  grid[99][0] = true;
  grid[99][99] = true;

  for (int iter = 0; iter < 100; iter++) {
    for (int y = 0; y < 100; y++) {
      for (int x = 0; x < 100; x++) {
        int surrounding = countSurrounding(x, y, grid);
        if ((x == 0 || x == 99) && y == 0 || (x == 0 || x == 99) && y == 99) {
          tempGrid[y][x] = true;
          continue;
        }
        if (grid[y][x]) {
          tempGrid[y][x] = surrounding == 2 || surrounding == 3;
        } else {
          tempGrid[y][x] = surrounding == 3;
        }
      }
    }
    grid = tempGrid;
  }

  auto countLights = [&]() {
    int count = 0;
    for (int y = 0; y < 100; y++) {
      for (int x = 0; x < 100; x++) {
        if (grid[y][x]) count++;
      }
    }
    return count;
  };

  return to_string(countLights());
}
