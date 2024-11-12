#ifndef AOC_YEAR__HPP
#define AOC_YEAR__HPP

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
#include "Day13.hpp"
#include "Day14.hpp"
#include "Day15.hpp"
#include "Day16.hpp"
#include "Day17.hpp"
#include "Day18.hpp"
#include "Day19.hpp"
#include "Day20.hpp"
#include "Day21.hpp"
#include "Day22.hpp"
#include "Day23.hpp"
#include "Day24.hpp"
#include "Day25.hpp"

class AoCYear_: public AoCYear {
public:
	AoCYear_() {
		setDay(1, std::make_shared<Day01_>(Day01_()));
		setDay(2, std::make_shared<Day02_>(Day02_()));
		setDay(3, std::make_shared<Day03_>(Day03_()));
		setDay(4, std::make_shared<Day04_>(Day04_()));
		setDay(5, std::make_shared<Day05_>(Day05_()));
		setDay(6, std::make_shared<Day06_>(Day06_()));
		setDay(7, std::make_shared<Day07_>(Day07_()));
		setDay(8, std::make_shared<Day08_>(Day08_()));
		setDay(9, std::make_shared<Day09_>(Day09_()));
		setDay(10, std::make_shared<Day10_>(Day10_()));
		setDay(11, std::make_shared<Day11_>(Day11_()));
		setDay(12, std::make_shared<Day12_>(Day12_()));
		setDay(13, std::make_shared<Day13_>(Day13_()));
		setDay(14, std::make_shared<Day14_>(Day14_()));
		setDay(15, std::make_shared<Day15_>(Day15_()));
		setDay(16, std::make_shared<Day16_>(Day16_()));
		setDay(17, std::make_shared<Day17_>(Day17_()));
		setDay(18, std::make_shared<Day18_>(Day18_()));
		setDay(19, std::make_shared<Day19_>(Day19_()));
		setDay(20, std::make_shared<Day20_>(Day20_()));
		setDay(21, std::make_shared<Day21_>(Day21_()));
		setDay(22, std::make_shared<Day22_>(Day22_()));
		setDay(23, std::make_shared<Day23_>(Day23_()));
		setDay(24, std::make_shared<Day24_>(Day24_()));
		setDay(25, std::make_shared<Day25_>(Day25_()));
	}
};

#endif
