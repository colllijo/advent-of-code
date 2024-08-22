#include "2015/Day14.hpp"

#include <algorithm>
#include <climits>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

Day14_2015::Day14_2015() {
  exampleInput =
    "Comet can fly 14 km/s for 10 seconds, but then must rest for 127 seconds.\n"
    "Dancer can fly 16 km/s for 11 seconds, but then must rest for 162 seconds.";
}

struct Reindeer {
  string name;
  int speed;
  int duration;
  int rest;
  int distance = 0;
  int points = 0;
};

string Day14_2015::part1(const string& input, bool example) {
  vector<Reindeer> reindeer;
  int best = INT_MIN;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((\w+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.)"))) {
      reindeer.push_back({match[1], stoi(match[2]), stoi(match[3]), stoi(match[4]), 0, 0});
    }
  }

  for (const auto& r : reindeer) {
    int time = 0;
    int distance = 0;

    while (time < 2503) {
      distance += r.speed * min(r.duration, 2503 - time);
      time += r.duration + r.rest;
    }

    best = max(best, distance);
  }

  return to_string(best);
}

string Day14_2015::part2(const string& input, bool example) {
  vector<Reindeer> reindeer;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((\w+) can fly (\d+) km/s for (\d+) seconds, but then must rest for (\d+) seconds.)"))) {
      reindeer.push_back({match[1], stoi(match[2]), stoi(match[3]), stoi(match[4]), 0, 0});
    }
  }

  for (int time = 0; time <= (example ? 1000 : 2503); time++) {
    int maxDistance = 0;

    for (auto& r : reindeer) {
      r.distance += (time % (r.duration + r.rest) < r.duration) ? r.speed : 0;
      maxDistance = max(maxDistance, r.distance);
    }

    for (auto& r : reindeer)
      if (r.distance == maxDistance) r.points++;
  }

  return to_string(max_element(reindeer.begin(), reindeer.end(), [](const Reindeer& a, const Reindeer& b) { return a.points < b.points; })->points);
}
