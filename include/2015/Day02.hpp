#ifndef AOC_2015_DAY_02_HPP
#define AOC_2015_DAY_02_HPP

#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day02_2015: public AoCDay {
public:
  Day02_2015();

  string part1(const string& input, bool example = false) override;
  string part2(const string& input, bool example = false) override;
};

#endif
