#include "2015/Day09.hpp"

#include <algorithm>
#include <cwchar>
#include <queue>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

Day09_2015::Day09_2015() {
  exampleInput = "London to Dublin = 464\nLondon to Belfast = 518\nDublin to Belfast = 141";
}

typedef struct Node {
  string name;
  int distance;
  unordered_set<string> visited;
} Node;

string Day09_2015::part1(const string& input, bool example) {
  priority_queue<Node *, vector<Node *>, decltype([](Node* a, Node* b){ return a->distance > b->distance; })> queue;
  unordered_map<string, vector<pair<string, int>>> paths;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((.+) to (.+) = (\d+))"))) {
      paths[match[1]].push_back({ match[2], stoi(match[3]) });
      paths[match[2]].push_back({ match[1], stoi(match[3]) });
    }
  }

  for (const auto [name, data] : paths) {
    queue.push(new Node{ name, 0, { name } });
  }

  Node current = *queue.top(); queue.pop();

  while (current.visited.size() != paths.size()) {
    for (const auto [name, distance] : paths[current.name]) {
      if (current.visited.contains(name)) continue;

      Node *next = new Node{ name, current.distance + distance, current.visited };
      next->visited.insert(name);

      queue.push(next);
    }

    current = *queue.top(); queue.pop();
  }

  return to_string(current.distance);
}

string Day09_2015::part2(const string& input, bool example) {
  priority_queue<Node *, vector<Node *>, decltype([](Node* a, Node* b){ return a->distance < b->distance; })> queue;
  unordered_map<string, vector<pair<string, int>>> paths;
  int totalDistance = 0;

  stringstream stream(input); string line;
  while (getline(stream, line, '\n')) {
    smatch match;
    if (regex_search(line, match, regex(R"((.+) to (.+) = (\d+))"))) {
      paths[match[1]].push_back({ match[2], stoi(match[3]) });
      paths[match[2]].push_back({ match[1], stoi(match[3]) });
    }
  }

  for (const auto [name, data] : paths) {
    queue.push(new Node{ name, 0, { name } });
  }

  while (!queue.empty()) {
    Node current = *queue.top(); queue.pop();
    for (const auto [name, distance] : paths[current.name]) {
      if (current.visited.contains(name)) continue;

      Node *next = new Node{ name, current.distance + distance, current.visited };
      next->visited.insert(name);

      if (next->visited.size() == paths.size()) totalDistance = max(totalDistance, next->distance);
      else queue.push(next);
    }
  }

  return to_string(totalDistance);
}
