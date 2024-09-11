#include "2015/Day17.hpp"
#include <algorithm>
#include <climits>
#include <functional>
#include <sstream>
#include <vector>

Day17_2015::Day17_2015() {
  exampleInput = "";
}

string Day17_2015::part1(const string& input, bool example) {
  vector<int> containers;

  stringstream stream(input); string line;
  while(getline(stream, line))
    containers.push_back(stoi(line));

  sort(containers.begin(), containers.end(), greater<int>());

  function<int(int, vector<int>)> combinations = [&combinations](int remaining, const vector<int> &containers) -> int {
    if(remaining == 0) return 1;
    if(containers.empty()) return 0;

    int total = 0;
    for (int i = 0; i < containers.size(); i++)
      if(containers[i] <= remaining)
        total += combinations(remaining - containers[i], vector<int>(containers.begin() + i + 1, containers.end()));

    return total;
  };

  return to_string(combinations(150, containers));
}

string Day17_2015::part2(const string& input, bool example) {
  vector<int> containers;
  int minContainers = INT_MAX;
  int count = 0;

  stringstream stream(input); string line;
  while(getline(stream, line))
    containers.push_back(stoi(line));

  sort(containers.begin(), containers.end(), greater<int>());

  function<void(int, int, vector<int>)> combinations = [&combinations, &minContainers, &count](int remaining, int depth, const vector<int> &containers) -> void {
    if (depth > minContainers) return;
    if(containers.empty()) return;

    if(remaining == 0) {
      if (depth < minContainers) {
        minContainers = depth;
        count = 1;
      } else if (depth == minContainers) {
        count++;
      }
    } else {
      for (int i = 0; i < containers.size(); i++)
        if(containers[i] <= remaining)
          combinations(remaining - containers[i], depth + 1, vector<int>(containers.begin() + i + 1, containers.end()));
    }

  };

  combinations(150, 0, containers);
  return to_string(count);
}
