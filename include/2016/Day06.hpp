#ifndef AOC_2016_DAY_06_HPP
#define AOC_2016_DAY_06_HPP

#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day06_2016: public AoCDay {
public:
	Day06_2016();

	string part1(const string& input, bool example = false) override;
	string part2(const string& input, bool example = false) override;
};

#endif