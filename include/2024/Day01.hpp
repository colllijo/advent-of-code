#pragma once

#include <coll-aoc-runner/AoCDay.hpp>

using namespace std;

class Day01_2024: public AoCDay {
public:
	Day01_2024();

	string part1(const string& input, bool example = false) override;
	string part2(const string& input, bool example = false) override;
};