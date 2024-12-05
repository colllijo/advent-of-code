#include "2024/Day05.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

Day05_2024::Day05_2024()
{
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

vector<int> orderPages(const vector<int>& update, const unordered_map<int, unordered_set<int>>& rules)
{
	vector<int> ordered = update;
	sort(ordered.begin(), ordered.end(),
	     [&rules](int a, int b)
	     {
		     if (rules.contains(a) && rules.at(a).contains(b))
		     {
			     return true;
		     }
		     return false;
	     });
	return ordered;
}

string Day05_2024::part1(const string& input, bool example)
{
	unordered_map<int, unordered_set<int>> rules;
	vector<vector<int>> pages;

	bool ruleSection = true;
	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.empty())
		{
			ruleSection = false;
			continue;
		}

		if (ruleSection)
		{
			stringstream ss(line);
			string a, b;
			getline(ss, a, '|');
			getline(ss, b, '|');
			rules[stoi(a)].insert(stoi(b));
		}
		else
		{
			vector<int> update;

			stringstream ss(line);
			string a;
			while (getline(ss, a, ','))
			{
				update.push_back(stoi(a));
			}

			pages.push_back(update);
		}
	}

	long sum = 0;
	for (const auto& update : pages)
		if (update == orderPages(update, rules)) sum += update[update.size() / 2];

	return to_string(sum);
}

string Day05_2024::part2(const string& input, bool example)
{
	unordered_map<int, unordered_set<int>> rules;
	vector<vector<int>> pages;

	bool ruleSection = true;
	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.empty())
		{
			ruleSection = false;
			continue;
		}

		if (ruleSection)
		{
			stringstream ss(line);
			string a, b;
			getline(ss, a, '|');
			getline(ss, b, '|');
			rules[stoi(a)].insert(stoi(b));
		}
		else
		{
			vector<int> update;

			stringstream ss(line);
			string a;
			while (getline(ss, a, ','))
			{
				update.push_back(stoi(a));
			}

			pages.push_back(update);
		}
	}

	auto badPages = pages | std::ranges::views::filter([&rules](std::vector<int> update) { return update != orderPages(update, rules); });

	long sum = 0;
	for (auto& update : badPages) sum += orderPages(update, rules)[update.size() / 2];

	return to_string(sum);
}
