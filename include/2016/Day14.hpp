#ifndef AOC_2016_DAY_14_HPP
#define AOC_2016_DAY_14_HPP

#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day14_2016: public AoCDay {
public:
	Day14_2016();

	string part1(const string& input, bool example = false) override;
	string part2(const string& input, bool example = false) override;
};

#endif
