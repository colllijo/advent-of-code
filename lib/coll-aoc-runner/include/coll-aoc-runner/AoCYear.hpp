#ifndef COLL_AOC_RUNNER_AOC_YEAR_HPP
#define COLL_AOC_RUNNER_AOC_YEAR_HPP

#pragma once

#include <memory>
#include <unordered_map>

#include "AoCDay.hpp"

class AoCYear {
public:
  AoCYear();
  ~AoCYear();

  std::unordered_map<int, std::shared_ptr<AoCDay>> getDays() const { return days; }
  std::shared_ptr<AoCDay> getDay(int day) const { return days.at(day); }

  void setDay(int day, std::shared_ptr<AoCDay> aocDay) { days[day] = aocDay; }

  std::shared_ptr<AoCDay>& operator[](int day) { return days[day]; }
private:
  std::unordered_map<int, std::shared_ptr<AoCDay>> days {};
};

#endif
