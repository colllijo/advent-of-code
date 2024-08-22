#include "2015/Day13.hpp"

#include <algorithm>
#include <climits>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

Day13_2015::Day13_2015() {
  exampleInput =
    "Alice would gain 54 happiness units by sitting next to Bob.\n"
    "Alice would lose 79 happiness units by sitting next to Carol.\n"
    "Alice would lose 2 happiness units by sitting next to David.\n"
    "Bob would gain 83 happiness units by sitting next to Alice.\n"
    "Bob would lose 7 happiness units by sitting next to Carol.\n"
    "Bob would lose 63 happiness units by sitting next to David.\n"
    "Carol would lose 62 happiness units by sitting next to Alice.\n"
    "Carol would gain 60 happiness units by sitting next to Bob.\n"
    "Carol would gain 55 happiness units by sitting next to David.\n"
    "David would gain 46 happiness units by sitting next to Alice.\n"
    "David would lose 7 happiness units by sitting next to Bob.\n"
    "David would gain 41 happiness units by sitting next to Carol.";
}

string Day13_2015::part1(const string& input, bool example) {
  vector<string> people;
  unordered_map<string, unordered_map<string, int>> happiness;

  int bestHappiness = INT_MIN;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((\w+) would (gain|lose) (\d+) happiness units by sitting next to (\w+).)"))) {
      if (people.empty() || find(people.begin(), people.end(), match[1]) == people.end()) {
        people.push_back(match[1]);
      }

      happiness[match[1]][match[4]] = (match[2] == "gain" ? 1 : -1) * stoi(match[3]);
    }
  }

  do {
    int currentHappiness = 0;

    for (size_t i = 0; i < people.size(); i++) {
      currentHappiness +=
        happiness[people[i]][people[(i + 1) % people.size()]]
        + happiness[people[i]][people[(i + people.size() - 1) % people.size()]];
    }

    bestHappiness = max(bestHappiness, currentHappiness);
  } while (ranges::next_permutation(people).found);

  return to_string(bestHappiness);
}

string Day13_2015::part2(const string& input, bool example) {
  vector<string> people;
  unordered_map<string, unordered_map<string, int>> happiness;

  int bestHappiness = INT_MIN;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((\w+) would (gain|lose) (\d+) happiness units by sitting next to (\w+).)"))) {
      if (people.empty() || find(people.begin(), people.end(), match[1]) == people.end()) {
        people.push_back(match[1]);
      }

      happiness[match[1]][match[4]] = (match[2] == "gain" ? 1 : -1) * stoi(match[3]);
    }
  }

  // Add myself to the list of people
  for (const auto& person: people) {
    happiness["Me"][person] = 0;
    happiness[person]["Me"] = 0;
  }
  people.push_back("Me");

  do {
    int currentHappiness = 0;

    for (size_t i = 0; i < people.size(); i++) {
      currentHappiness +=
        happiness[people[i]][people[(i + 1) % people.size()]]
        + happiness[people[i]][people[(i + people.size() - 1) % people.size()]];
    }

    bestHappiness = max(bestHappiness, currentHappiness);
  } while (ranges::next_permutation(people).found);

  return to_string(bestHappiness);
}
