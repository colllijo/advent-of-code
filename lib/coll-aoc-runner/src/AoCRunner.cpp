#include "AoCRunner.hpp"

#include <cstdlib>
#include <cwchar>
#include <getopt.h>
#include <stdexcept>

AoCRunner::AoCRunner(): error(0), printHelpFlag(false), printVersionFlag(false), runExamples(true) { }
AoCRunner::~AoCRunner() = default;

void AoCRunner::addYear(int year, const AoCYear &aocYear) {
  years[year] = aocYear;
}

int AoCRunner::run(int argc, char *argv[]) {
  parseArgs(argc, argv);

  if (error) return error;
  if (printHelpFlag) return printHelp();
  if (printVersionFlag) return printVersion();

  for (const auto& [year, aocYear] : years) {
    if (selector.year != -1 && selector.year != year) continue;

    for (auto& [day, aocDay] : aocYear.getDays()) {
      if (selector.day != -1 && selector.day != day) continue;

      std::string input;
      if (selector.part != 2) {
        if (runExamples) runPart(year, day, 1, aocDay->part1(aocDay->getExampleInput(), true), true);
        runPart(year, day, 1, aocDay->part1(input));
      }
      if (selector.part != 1) {
        if (runExamples) runPart(year, day, 2, aocDay->part2(aocDay->getExampleInput(), true), true);
        runPart(year, day, 2, aocDay->part2(input));
      }
    }
  }

  return 0;
}

void AoCRunner::runPart(int year, int day, int part, const std::string &result, bool example) {
  if (result.empty()) return;

  wprintf(L"%d-%02d Part %d %s: %s\n", year, day, part, example ? "Example" : "", result.c_str());
}

void AoCRunner::parseArgs(int argc, char *argv[]) {
  const struct option longopts[] = {
    {"help", no_argument, nullptr, 'h'},
    {"version", no_argument, nullptr, 'v'},
    {"year", required_argument, nullptr, 'y'},
    {"day", required_argument, nullptr, 'd'},
    {"part", required_argument, nullptr, 'p'},
    {"no-example", no_argument, nullptr, 'x'},
    {nullptr, 0, nullptr, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "hvy:d:p:", longopts, nullptr)) != -1) {
    switch (opt) {
      case 'h':
        printHelpFlag = true;
        return;
      case 'v':
        printVersionFlag = true;
        return;
      case 'y':
        selector.year = parseArgToInt("year", optarg);
        break;
      case 'd':
        selector.day = parseArgToInt("day", optarg);
        break;
      case 'p':
        selector.part = parseArgToInt("part", optarg);
        break;
      case 'x':
        runExamples = false;
        break;
    }
  }

  validateSelector();
}

int AoCRunner::parseArgToInt(const char *option, char *arg) {
  try {
    return std::stoi(arg);
  } catch (std::invalid_argument &e) {
    fwprintf(stderr, L"\033[91mError:\033[0m Invalid argument for option %s, (%s)\n", option, arg);
    error = 1;
  } catch (std::out_of_range &e) {
    fwprintf(stderr, L"\033[91mError:\033[0m Argument out of range for option %s (%s)\n", option, arg);
    error = 1;
  }

  return -1;
}

void AoCRunner::validateSelector() {
  if (selector.year != -1 && selector.year < 2015) {
    fwprintf(stderr, L"\033[91mError:\033[0m Invalid year %d\n", selector.year);
    error = 1;
  }
  if (selector.day != -1 && (selector.day < 1 || selector.day > 25)) {
    fwprintf(stderr, L"\033[91mError:\033[0m Invalid day %d\n", selector.day);
    error = 1;
  }
  if (selector.part != -1 && (selector.part < 1 || selector.part > 2)) {
    fwprintf(stderr, L"\033[91mError:\033[0m Invalid part %d\n", selector.part);
    error = 1;
  }
}

int AoCRunner::printVersion() {
  wprintf(L"Advent of Code Runner v0.1\n");

  return 0;
}

int AoCRunner::printHelp() {
  wprintf(L"Usage: aoc-runner [options]\n");

  return 0;
}
