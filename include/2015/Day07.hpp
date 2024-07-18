#ifndef AOC_2015_DAY_07_HPP
#define AOC_2015_DAY_07_HPP

#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day07_2015: public AoCDay {
public:
  Day07_2015();

  string part1(const string& input, bool example = false) override;
  string part2(const string& input, bool example = false) override;
};

#endif
