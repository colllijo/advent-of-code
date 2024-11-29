#pragma once

#include <string>

class AoCDay {
public:
  AoCDay();
  ~AoCDay();

  virtual std::string part1(const std::string& input, bool example = false);
  virtual std::string part2(const std::string& input, bool example = false);

  bool hasExampleInput() const { return !exampleInput.empty(); }
  std::string getExampleInput() const { return exampleInput; }

protected:
  std::string exampleInput;
};
