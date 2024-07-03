#ifndef COLL_AOC_RUNNER_AOC_YEAR_HPP
#define COLL_AOC_RUNNER_AOC_YEAR_HPP

#pragma once

#include <unordered_map>

#include "AoCDay.hpp"

class AoCYear {
public:
  AoCYear();
  ~AoCYear();

  std::unordered_map<int, AoCDay> getDays() const { return days; }
  AoCDay getDay(int day) const { return days.at(day); }

  void setDay(int day, AoCDay dayObj) { days[day] = dayObj; }

  AoCDay& operator[](int day) { return days[day]; }
private:
  std::unordered_map<int, AoCDay> days {};
};

#endif
