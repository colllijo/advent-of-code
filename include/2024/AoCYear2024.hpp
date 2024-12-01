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

class AoCYear_2024: public AoCYear {
public:
	AoCYear_2024() {
		setDay(1, std::make_shared<Day01_2024>(Day01_2024()));
		setDay(2, std::make_shared<Day02_2024>(Day02_2024()));
		setDay(3, std::make_shared<Day03_2024>(Day03_2024()));
		setDay(4, std::make_shared<Day04_2024>(Day04_2024()));
		setDay(5, std::make_shared<Day05_2024>(Day05_2024()));
		setDay(6, std::make_shared<Day06_2024>(Day06_2024()));
		setDay(7, std::make_shared<Day07_2024>(Day07_2024()));
		setDay(8, std::make_shared<Day08_2024>(Day08_2024()));
		setDay(9, std::make_shared<Day09_2024>(Day09_2024()));
		setDay(10, std::make_shared<Day10_2024>(Day10_2024()));
		setDay(11, std::make_shared<Day11_2024>(Day11_2024()));
		setDay(12, std::make_shared<Day12_2024>(Day12_2024()));
		setDay(13, std::make_shared<Day13_2024>(Day13_2024()));
		setDay(14, std::make_shared<Day14_2024>(Day14_2024()));
		setDay(15, std::make_shared<Day15_2024>(Day15_2024()));
		setDay(16, std::make_shared<Day16_2024>(Day16_2024()));
		setDay(17, std::make_shared<Day17_2024>(Day17_2024()));
		setDay(18, std::make_shared<Day18_2024>(Day18_2024()));
		setDay(19, std::make_shared<Day19_2024>(Day19_2024()));
		setDay(20, std::make_shared<Day20_2024>(Day20_2024()));
		setDay(21, std::make_shared<Day21_2024>(Day21_2024()));
		setDay(22, std::make_shared<Day22_2024>(Day22_2024()));
		setDay(23, std::make_shared<Day23_2024>(Day23_2024()));
		setDay(24, std::make_shared<Day24_2024>(Day24_2024()));
		setDay(25, std::make_shared<Day25_2024>(Day25_2024()));
	}
};
