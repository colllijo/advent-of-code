#include "2015/Day02.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <charconv>
#include <string>

Day02_2015::Day02_2015() {
  exampleInput = "2x3x4\n1x1x10";
}

void extractDimensions(const string& str, int& w, int& l, int& h) {
    const char* ptr = str.data();
    const char* end = ptr + str.size();
    ptr = from_chars(ptr, end, w).ptr + 1;
    ptr = from_chars(ptr, end, l).ptr + 1;
    from_chars(ptr, end, h);
}

string Day02_2015::part1(const string& input, bool example) {
  int wrappingPaper = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    int w, l, h;
    extractDimensions(line, w, l, h);

    wrappingPaper += 2 * (w * l + l * h + h * w) + min({w * l, l * h, h * w});
  }

  return to_string(wrappingPaper);
}

string Day02_2015::part2(const string& input, bool example) {
  int ribbonLength = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    int w, l, h;
    extractDimensions(line, w, l, h);

    ribbonLength += 2 * (w + l + h - max({w, l, h})) + w * l * h;
  }

  return to_string(ribbonLength);
}
