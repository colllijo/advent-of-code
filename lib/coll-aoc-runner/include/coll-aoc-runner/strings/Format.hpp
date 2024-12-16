#pragma once

#include <regex>
#include <string>
#include <vector>

namespace caoc::strings
{
  std::string trim(const std::string& str, const std::string& whitespace = " \t\n\r");
  std::vector<std::string> split(const std::string& str, const std::string& delimiter);
  std::vector<std::string> split(const std::string& str, const std::regex& delimiter);
};
