#include <coll-aoc-runner/AoCRunner.hpp>

#include "AoCYears.hpp"

int main(int argc, char *argv[]) {
  auto runner = AoCRunner();

  // Add years to the runner
  runner.addYear(2015, AoCYear_2015());

  return runner.run(argc, argv);
}
