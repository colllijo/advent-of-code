#include "2016/Day10.hpp"

#include <algorithm>
#include <regex>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

Day10_2016::Day10_2016()
{
	exampleInput =
	    "value 5 goes to bot 2\n"
	    "bot 2 gives low to bot 1 and high to bot 0\n"
	    "value 3 goes to bot 1\n"
	    "bot 1 gives low to output 1 and high to bot 0\n"
	    "bot 0 gives low to output 2 and high to output 0\n"
	    "value 2 goes to bot 2";
}

string Day10_2016::part1(const string& input, bool example)
{
	// Bot id -> chips
	unordered_map<int, vector<int>> bots;
	// Bot id -> (low, high)
	unordered_map<int, tuple<string, int, string, int>> rules;
	// Output id -> chips
	unordered_map<int, vector<int>> outputs;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		smatch match;

		if (line.starts_with("value"))
		{
			if (regex_search(line, match, regex(R"(value (\d+) goes to bot (\d+))")))
			{
				int value = stoi(match[1]);
				int bot = stoi(match[2]);

				if (bots.contains(bot))
					bots[bot].push_back(value);
				else
					bots[bot] = {value};
			}
		}
		else
		{
			if (regex_search(line, match, regex(R"(bot (\d+) gives low to (output|bot) (\d+) and high to (output|bot) (\d+))")))
			{
				int bot = stoi(match[1]);
				int low = stoi(match[3]);
				int high = stoi(match[5]);

				rules[bot] = {match[2], low, match[4], high};
			}
		}
	}

	auto done = [&bots]() -> bool {
		bool done = true;

		for (auto& [id, chips] : bots)
		{
			if (chips.size() == 2)
			{
				done = false;
				break;
			}
		}

		return done;
	};

	while (!done())
	{
		for (const auto& [bot, chips] : bots)
		{
			if (chips.size() != 2) continue;

			sort(bots[bot].begin(), bots[bot].end());

			if (example && bots[bot] == vector<int>{2, 5}) return to_string(bot);
			if (!example && bots[bot] == vector<int>{17, 61}) return to_string(bot);

			const auto& [lowTo, lowId, highTo, highId] = rules[bot];

			if (lowTo == "output")
			{
				if (outputs.contains(lowId)) outputs[lowId].push_back(chips[0]);
				else outputs[lowId] = {chips[0]};
			}
			else
			{
				if (bots.contains(lowId)) bots[lowId].push_back(chips[0]);
				else bots[lowId] = {chips[0]};
			}

			if (highTo == "output")
			{
				if (outputs.contains(highId)) outputs[highId].push_back(chips[1]);
				else outputs[highId] = {chips[1]};
			}
			else
			{
				if (bots.contains(highId)) bots[highId].push_back(chips[1]);
				else bots[highId] = {chips[1]};
			}

			bots[bot].clear();
		}
	}

	return "Not found";
}

string Day10_2016::part2(const string& input, bool example)
{
	// Bot id -> chips
	unordered_map<int, vector<int>> bots;
	// Bot id -> (low, high)
	unordered_map<int, tuple<string, int, string, int>> rules;
	// Output id -> chips
	unordered_map<int, vector<int>> outputs;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		smatch match;

		if (line.starts_with("value"))
		{
			if (regex_search(line, match, regex(R"(value (\d+) goes to bot (\d+))")))
			{
				int value = stoi(match[1]);
				int bot = stoi(match[2]);

				if (bots.contains(bot))
					bots[bot].push_back(value);
				else
					bots[bot] = {value};
			}
		}
		else
		{
			if (regex_search(line, match, regex(R"(bot (\d+) gives low to (output|bot) (\d+) and high to (output|bot) (\d+))")))
			{
				int bot = stoi(match[1]);
				int low = stoi(match[3]);
				int high = stoi(match[5]);

				rules[bot] = {match[2], low, match[4], high};
			}
		}
	}

	auto done = [&bots]() -> bool {
		bool done = true;

		for (auto& [id, chips] : bots)
		{
			if (chips.size() == 2)
			{
				done = false;
				break;
			}
		}

		return done;
	};

	while (!done())
	{
		for (const auto& [bot, chips] : bots)
		{
			if (chips.size() != 2) continue;

			sort(bots[bot].begin(), bots[bot].end());

			const auto& [lowTo, lowId, highTo, highId] = rules[bot];

			if (lowTo == "output")
			{
				if (outputs.contains(lowId)) outputs[lowId].push_back(chips[0]);
				else outputs[lowId] = {chips[0]};
			}
			else
			{
				if (bots.contains(lowId)) bots[lowId].push_back(chips[0]);
				else bots[lowId] = {chips[0]};
			}

			if (highTo == "output")
			{
				if (outputs.contains(highId)) outputs[highId].push_back(chips[1]);
				else outputs[highId] = {chips[1]};
			}
			else
			{
				if (bots.contains(highId)) bots[highId].push_back(chips[1]);
				else bots[highId] = {chips[1]};
			}

			bots[bot].clear();
		}
	}

	if (!example)
	{
		return to_string(outputs[0][0] * outputs[1][0] * outputs[2][0]);
	}
	return "";
}
