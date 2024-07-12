#ifndef COLL_AOC_RUNNER_AOC_RUNNER_HPP
#define COLL_AOC_RUNNER_AOC_RUNNER_HPP

#include <string>
#pragma once

#include <unordered_map>

#include "AoCSelector.hpp"
#include "AoCYear.hpp"

class AoCRunner {
public:
  AoCRunner();
  ~AoCRunner();

  void addYear(int year, const AoCYear &aocYear);

  int run(int argc, char *argv[]);

private:
  std::unordered_map<int, AoCYear> years;
  AoCSelector selector;

  int error;

  bool printHelpFlag;
  bool printVersionFlag;

  bool runExamples;

  void parseArgs(int argc, char *argv[]);
  int parseArgToInt(const char *option, char *arg);

  void validateSelector();

  void runPart(int year, int day, int part, const std::string &result, bool example = false);

  int printVersion();
  int printHelp();
};

#endif
