#include "2015/Day04.hpp"

#include "coll-aoc-runner/crypto/MD5.hpp"


Day04_2015::Day04_2015() {
  exampleInput = "abcdef";
}

string Day04_2015::part1(const string& input, bool example) {
  int i = 1;

  while (i > 0) {
    string hash = caoc::crypto::md5(input + to_string(i));
    if (hash.starts_with("00000")) break;
    i++;
  }

  return to_string(i);
}

string Day04_2015::part2(const string& input, bool example) {
  int i = 1;

  while (i > 0) {
    string hash = caoc::crypto::md5(input + to_string(i));
    if (hash.starts_with("000000")) break;
    i++;
  }

  return to_string(i);
}
