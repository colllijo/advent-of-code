#include <coll-aoc-runner/AoCRunner.hpp>

#include "AoCYears.hpp"

int main(int argc, char *argv[]) {
  auto runner = AoCRunner();

  // Add years to the runner
  runner.addYear(2015, AoCYear_2015());
  runner.addYear(2016, AoCYear_2016());

  return runner.run(argc, argv);
}
