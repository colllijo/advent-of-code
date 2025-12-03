#pragma once

#include <memory>

#include <coll-aoc-runner/AoCYear.hpp>

#include "Day01.hpp"
#include "Day02.hpp"
#include "Day03.hpp"
#include "Day04.hpp"
#include "Day05.hpp"
#include "Day06.hpp"
#include "Day07.hpp"
#include "Day08.hpp"
#include "Day09.hpp"
#include "Day10.hpp"
#include "Day11.hpp"
#include "Day12.hpp"

class AoCYear_2025: public AoCYear {
public:
	AoCYear_2025() {
		setDay(1, std::make_shared<Day01_2025>(Day01_2025()));
		setDay(2, std::make_shared<Day02_2025>(Day02_2025()));
		setDay(3, std::make_shared<Day03_2025>(Day03_2025()));
		setDay(4, std::make_shared<Day04_2025>(Day04_2025()));
		setDay(5, std::make_shared<Day05_2025>(Day05_2025()));
		setDay(6, std::make_shared<Day06_2025>(Day06_2025()));
		setDay(7, std::make_shared<Day07_2025>(Day07_2025()));
		setDay(8, std::make_shared<Day08_2025>(Day08_2025()));
		setDay(9, std::make_shared<Day09_2025>(Day09_2025()));
		setDay(10, std::make_shared<Day10_2025>(Day10_2025()));
		setDay(11, std::make_shared<Day11_2025>(Day11_2025()));
		setDay(12, std::make_shared<Day12_2025>(Day12_2025()));
	}
};
