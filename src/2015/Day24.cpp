#include "2015/Day24.hpp"

#include <climits>
#include <set>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>

Day24_2015::Day24_2015() { exampleInput = "1\n2\n3\n4\n5\n7\n8\n9\n10\n11"; }

string Day24_2015::part1(const string& input, bool example)
{
	vector<int> packages;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		packages.push_back(stoi(line));
	}

	sort(packages.begin(), packages.end(), greater<int>());
  int targetWeight = accumulate(packages.begin(), packages.end(), 0) / 3;
	int third = packages.size() / 3;

  set<pair<int, long>> combinations{};
  auto calc = [&combinations, &targetWeight, &third](auto& calc, const vector<int> packages, int sum = 0, int count = 0, long qe = 1) -> void
  {
    if (sum == targetWeight)
    {
        combinations.insert({count, qe});
    }
    else if (sum < targetWeight && !packages.empty() && count < third)
    {
      auto package = packages.back();
      auto newPackages = packages;
      newPackages.pop_back();

      calc(calc, newPackages, sum, count, qe);
      calc(calc, newPackages, sum + package, count + 1, qe * package);
    }
  };

  calc(calc, packages);
  if (combinations.empty())
  {
    return "No solution found.";
  }

  long result = LONG_MAX;
  auto minCount = combinations.begin()->first;

  for (auto& [count, qe] : combinations)
  {
    if (count < minCount)
    {
      result = qe;
      continue;
    }
    if (count == minCount)
    {
      result = min(result, qe);
    }
  }

	return to_string(result);
}

string Day24_2015::part2(const string& input, bool example)
{
  vector<int> packages;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		packages.push_back(stoi(line));
	}

	sort(packages.begin(), packages.end(), greater<int>());
  int targetWeight = accumulate(packages.begin(), packages.end(), 0) / 4;
	int third = packages.size() / 4;

  set<pair<int, long>> combinations{};
  auto calc = [&combinations, &targetWeight, &third](auto& calc, const vector<int> packages, int sum = 0, int count = 0, long qe = 1) -> void
  {
    if (sum == targetWeight)
    {
        combinations.insert({count, qe});
    }
    else if (sum < targetWeight && !packages.empty() && count < third)
    {
      auto package = packages.back();
      auto newPackages = packages;
      newPackages.pop_back();

      calc(calc, newPackages, sum, count, qe);
      calc(calc, newPackages, sum + package, count + 1, qe * package);
    }
  };

  calc(calc, packages);
  if (combinations.empty())
  {
    return "No solution found.";
  }

  long result = LONG_MAX;
  auto minCount = combinations.begin()->first;

  for (auto& [count, qe] : combinations)
  {
    if (count < minCount)
    {
      result = qe;
      continue;
    }
    if (count == minCount)
    {
      result = min(result, qe);
    }
  }

	return to_string(result);
}
