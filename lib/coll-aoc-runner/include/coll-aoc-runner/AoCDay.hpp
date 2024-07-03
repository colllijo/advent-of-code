#ifndef COLL_AOC_RUNNER_AOC_DAY_HPP
#define COLL_AOC_RUNNER_AOC_DAY_HPP

#pragma once

#include <string>

class AoCDay {
public:
  AoCDay();
  ~AoCDay();

  std::string part1(const std::string& input, bool example = false);
  std::string part2(const std::string& input, bool example = false);

  std::string getExampleInput() const { return exampleInput; }

private:
  std::string exampleInput;
};

#endif
