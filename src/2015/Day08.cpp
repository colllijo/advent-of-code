#include "2015/Day08.hpp"
#include <algorithm>
#include <cwchar>
#include <sstream>
#include <string>

Day08_2015::Day08_2015() {
  exampleInput = "\"\"\n\"abc\"\n\"aaa\\\"aaa\"\n\"\\x27\"";
}

string Day08_2015::part1(const string& input, bool example) {
  int code = 0;
  int memory = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    code += line.size();
    memory += line.size();

    size_t pos = line.find("\\");
    while(pos != string::npos) {
      if (line[pos + 1] == 'x') {
        memory -= 3;
        pos += 4;
      } else {
        memory -= 1;
        pos += 2;
      }

      pos = line.find("\\", pos);
    }

    memory -= 2; // Remove start and end quote
  }

  return to_string(code - memory);
}

string Day08_2015::part2(const string& input, bool example) {
  int code = 0;
  int encoded = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    code += line.size();
    encoded += line.size();

    encoded += 2; // Add start and end quote
    encoded += count(line.begin(), line.end(), '\\');
    encoded += count(line.begin(), line.end(), '"');
  }

  return to_string(encoded - code);
}
