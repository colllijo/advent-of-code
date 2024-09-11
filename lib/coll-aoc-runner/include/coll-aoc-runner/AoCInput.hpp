#ifndef COLL_AOC_RUNNER_AOC_INPUT_HPP
#define COLL_AOC_RUNNER_AOC_INPUT_HPP

#include <filesystem>
#include <string>

#pragma once

class AoCInput {
public:
  AoCInput();
  ~AoCInput();

  std::string getInput(int year, int day);

private:
  std::filesystem::path inputDir;
  std::string authCookie;

  void loadAuthCookie();
  void downloadInput(int year, int day);
};

#endif
