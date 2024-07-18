#ifndef AOC_YEAR_2015_HPP
#define AOC_YEAR_2015_HPP

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

class AoCYear_2015: public AoCYear {
public:
  AoCYear_2015() {
    setDay(1, std::make_shared<Day01_2015>(Day01_2015()));
    setDay(2, std::make_shared<Day02_2015>(Day02_2015()));
    setDay(3, std::make_shared<Day03_2015>(Day03_2015()));
    setDay(4, std::make_shared<Day04_2015>(Day04_2015()));
    setDay(5, std::make_shared<Day05_2015>(Day05_2015()));
    setDay(6, std::make_shared<Day06_2015>(Day06_2015()));
    setDay(7, std::make_shared<Day07_2015>(Day07_2015()));
    setDay(8, std::make_shared<Day08_2015>(Day08_2015()));
    setDay(9, std::make_shared<Day09_2015>(Day09_2015()));
    setDay(10, std::make_shared<Day10_2015>(Day10_2015()));
    setDay(11, std::make_shared<Day11_2015>(Day11_2015()));
    setDay(12, std::make_shared<Day12_2015>(Day12_2015()));
    setDay(13, std::make_shared<Day13_2015>(Day13_2015()));
    setDay(14, std::make_shared<Day14_2015>(Day14_2015()));
    setDay(15, std::make_shared<Day15_2015>(Day15_2015()));
    setDay(16, std::make_shared<Day16_2015>(Day16_2015()));
    setDay(17, std::make_shared<Day17_2015>(Day17_2015()));
    setDay(18, std::make_shared<Day18_2015>(Day18_2015()));
    setDay(19, std::make_shared<Day19_2015>(Day19_2015()));
    setDay(20, std::make_shared<Day20_2015>(Day20_2015()));
    setDay(21, std::make_shared<Day21_2015>(Day21_2015()));
    setDay(22, std::make_shared<Day22_2015>(Day22_2015()));
    setDay(23, std::make_shared<Day23_2015>(Day23_2015()));
    setDay(24, std::make_shared<Day24_2015>(Day24_2015()));
    setDay(25, std::make_shared<Day25_2015>(Day25_2015()));
  }
};

#endif
