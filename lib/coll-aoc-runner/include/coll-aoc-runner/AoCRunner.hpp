#ifndef COLL_AOC_RUNNER_AOC_RUNNER_HPP
#define COLL_AOC_RUNNER_AOC_RUNNER_HPP

#include "AoCInput.hpp"
#include <memory>
#pragma once

#include <map>

#include "AoCSelector.hpp"
#include "AoCYear.hpp"
#include "AoCDay.hpp"

class AoCRunner {
public:
  AoCRunner();
  ~AoCRunner();

  void addYear(int year, const AoCYear &aocYear);

  int run(int argc, char *argv[]);

private:
  std::map<int, AoCYear> years;
  AoCSelector selector;
  AoCInput aocInput;

  bool runExamples;

  void parseArgs(int argc, char *argv[]);
  int parseArgToInt(const char *option, char *arg);
  void validateAoCSelector();

  void runPart(const std::shared_ptr<AoCDay> &aocDay, int year, int day, int part, bool example = false);

  void printVersion();
  void printHelp();
};

#endif
