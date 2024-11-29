#pragma once

#include <memory>
#include <map>

#include "AoCDay.hpp"

class AoCYear {
public:
  AoCYear();
  ~AoCYear();

  std::map<int, std::shared_ptr<AoCDay>> getDays() const { return days; }
  std::shared_ptr<AoCDay> getDay(int day) const { return days.at(day); }

  void setDay(int day, std::shared_ptr<AoCDay> aocDay) { days[day] = aocDay; }

  std::shared_ptr<AoCDay>& operator[](int day) { return days[day]; }
private:
  std::map<int, std::shared_ptr<AoCDay>> days {};
};
