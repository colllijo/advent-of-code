#ifndef AOC_2016_DAY_04_HPP
#define AOC_2016_DAY_04_HPP

#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day04_2016: public AoCDay {
public:
	Day04_2016();

	string part1(const string& input, bool example = false) override;
	string part2(const string& input, bool example = false) override;
};

#endif
