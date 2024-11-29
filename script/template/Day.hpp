#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day_: public AoCDay {
public:
	Day_();

	string part1(const string& input, bool example = false) override;
	string part2(const string& input, bool example = false) override;
};
