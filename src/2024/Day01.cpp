#include "2024/Day01.hpp"

#include <algorithm>
#include <ranges>

Day01_2024::Day01_2024()
{
	exampleInput =
	    "3   4\n"
	    "4   3\n"
	    "2   5\n"
	    "1   3\n"
	    "3   9\n"
	    "3   3";
}

string Day01_2024::part1(const string& input, bool example)
{
	auto leftView = strings::split(input, "\n")
    | ranges::views::transform([](const auto& line) { return strings::split(line, regex("\\s+"))[0]; })
    | ranges::views::transform([](const auto& str) { return stoi(str); });

	auto rightView = strings::split(input, "\n")
	   | ranges::views::transform([](const auto& line) { return strings::split(line, regex("\\s+"))[1]; })
	   | ranges::views::transform([](const auto& str) { return stoi(str); });

	vector<int> left(leftView.begin(), leftView.end());
	vector<int> right(rightView.begin(), rightView.end());

  ranges::sort(left);
  ranges::sort(right);

  return to_string(ranges::fold_left(
    ranges::views::zip_transform([](int left, int right){ return abs(left - right); }, left, right),
    0,
    plus<>()
  ));
}

string Day01_2024::part2(const string& input, bool example)
{
	auto leftView = strings::split(input, "\n")
    | ranges::views::transform([](const auto& line) { return strings::split(line, regex("\\s+"))[0]; })
    | ranges::views::transform([](const auto& str) { return stoi(str); });

	auto rightView = strings::split(input, "\n")
    | ranges::views::transform([](const auto& line) { return strings::split(line, regex("\\s+"))[1]; })
    | ranges::views::transform([](const auto& str) { return stoi(str); });

  auto freqMap = ranges::fold_left(
    rightView,
    unordered_map<int, int>(),
    [](auto acc, int val) {
      if (!acc.count(val))
        acc[val] = 1;
      else
        acc[val]++;

      return acc;
    }
  );

	vector<int> left(leftView.begin(), leftView.end());

  return to_string(ranges::fold_left(
    left,
    0,
    [&freqMap](int acc, int val){ return acc + (val * freqMap[val]); }
  ));
}
