#pragma once

#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <regex>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

using namespace std;
using namespace caoc;
using namespace caoc::structs;

class AoCDay {
public:
  AoCDay();
  ~AoCDay();

  virtual std::string part1(const std::string& input, bool example = false);
  virtual std::string part2(const std::string& input, bool example = false);

  bool hasExampleInput() const { return !exampleInput.empty(); }
  std::string getExampleInput() const { return exampleInput; }

protected:
  std::string exampleInput;
};
