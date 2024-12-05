#include "2024/Day05.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

Day05_2024::Day05_2024() {
	exampleInput = 
"47|53\n"
"97|13\n"
"97|61\n"
"97|47\n"
"75|29\n"
"61|13\n"
"75|53\n"
"29|13\n"
"97|29\n"
"53|29\n"
"61|53\n"
"97|53\n"
"61|29\n"
"47|13\n"
"75|47\n"
"97|75\n"
"47|61\n"
"75|61\n"
"47|29\n"
"75|13\n"
"53|13\n"
"\n"
"75,47,61,53,29\n"
"97,61,53,29,13\n"
"75,29,13\n"
"75,97,47,61,53\n"
"61,13,29\n"
"97,13,75,29,47";
}

string Day05_2024::part1(const string& input, bool example) {
	unordered_map<int, unordered_set<int>> after;
	unordered_map<int, unordered_set<int>> before;

	vector<vector<int>>pages;

	bool rules = true;
	stringstream stream(input); string line;
	while (getline(stream, line))
	{
		if (line.empty()) {
			rules = false;
			continue;
		}

		if (rules) {
			stringstream ss(line); string a, b;
			getline(ss, a, '|'); getline(ss, b, '|');
			int x = stoi(a), y = stoi(b);
			after[x].insert(y);
			before[y].insert(x);
		}
		else {
			vector<int> update;

			stringstream ss(line); string a;
			while (getline(ss, a, ',')) {
				update.push_back(stoi(a));
			}

			pages.push_back(update);
		}
	}

	long sum = 0;

	for (const auto& update : pages)
	{
		bool valid = true;
		for (int i = 0; i < update.size(); i++)
		{
			int page = update[i];

			for (const auto& rule : before[page])
			{
				if (find(update.begin(), update.end(), rule) != update.end())
				{
					bool found = false;
					for (int j = 0; j < i; j++)
					{
						if (update[j] == rule)
						{
							found = true;
							break;
						}
					}
					valid &= found;
				}
			}

			for (const auto& rule : after[page])
			{
				if (find(update.begin(), update.end(), rule) != update.end())
				{
					bool found = false;
					for (int j = i + 1; j < update.size(); j++)
					{
						if (update[j] == rule)
						{
							found = true;
							break;
						}
					}
					valid &= found;
				}
			}
		}

		if (valid) {
			sum += update[update.size() / 2];
		}
	}

	return to_string(sum);
}

string Day05_2024::part2(const string& input, bool example) {
	unordered_map<int, unordered_set<int>> after;
	unordered_map<int, unordered_set<int>> before;

	vector<vector<int>>pages;

	bool rules = true;
	stringstream stream(input); string line;
	while (getline(stream, line))
	{
		if (line.empty()) {
			rules = false;
			continue;
		}

		if (rules) {
			stringstream ss(line); string a, b;
			getline(ss, a, '|'); getline(ss, b, '|');
			int x = stoi(a), y = stoi(b);
			after[x].insert(y);
			before[y].insert(x);
		}
		else {
			vector<int> update;

			stringstream ss(line); string a;
			while (getline(ss, a, ',')) {
				update.push_back(stoi(a));
			}

			pages.push_back(update);
		}
	}

	auto badPages = pages | std::ranges::views::filter([&before, &after](std::vector<int> update) {
		bool valid = true;
		for (int i = 0; i < update.size(); i++)
		{
			int page = update[i];

			for (const auto& rule : before[page])
			{
				if (find(update.begin(), update.end(), rule) != update.end())
				{
					bool found = false;
					for (int j = 0; j < i; j++)
					{
						if (update[j] == rule)
						{
							found = true;
							break;
						}
					}
					valid &= found;
				}
			}

			for (const auto& rule : after[page])
			{
				if (find(update.begin(), update.end(), rule) != update.end())
				{
					bool found = false;
					for (int j = i + 1; j < update.size(); j++)
					{
						if (update[j] == rule)
						{
							found = true;
							break;
						}
					}
					valid &= found;
				}
			}
		}

		return !valid;
	});

	long sum = 0;
	for (auto& update : badPages)
	{
		sort(update.begin(), update.end(), [&before, &after](int a, int b){
			if (after[a].contains(b))
			{
				return true;
			}
			return false;
		});

		sum += update[update.size() / 2];
	}

	return to_string(sum);
}
