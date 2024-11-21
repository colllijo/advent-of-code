#include "2016/Day04.hpp"

#include <algorithm>
#include <map>
#include <regex>
#include <sstream>

Day04_2016::Day04_2016()
{
	exampleInput =
	    "aaaaa-bbb-z-y-x-123[abxyz]\n"
	    "a-b-c-d-e-f-g-h-987[abcde]\n"
	    "not-a-real-room-404[oarel]\n"
	    "totally-real-room-200[decoy]\n";
}

string calculateChecksum(string name)
{
	map<char, int> counts;
	for (char c : name)
	{
		if (c == '-') continue;
		counts[c]++;
	}

	vector<pair<char, int>> sorted;
	for (const auto& pair : counts)
	{
		sorted.push_back(pair);
	}

	sort(sorted.begin(), sorted.end(),
	     [](const pair<char, int>& a, const pair<char, int>& b)
	     {
		     if (a.second != b.second) return a.second > b.second;
		     return a.first < b.first;
	     });

	string calculatedChecksum;
	for (int i = 0; i < 5; i++)
	{
		calculatedChecksum += sorted[i].first;
	}

  return calculatedChecksum;
}

string Day04_2016::part1(const string& input, bool example)
{
	int sum = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		smatch match;

		if (regex_search(line, match, regex("([a-z-]+)-([0-9]+)\\[([a-z]+)\\]")))
		{
			string name = match[1];
			int id = stoi(match[2]);
			string checksum = match[3];

			if (calculateChecksum(name) == checksum)
			{
				sum += id;
			}
		}
	}

	return to_string(sum);
}

string Day04_2016::part2(const string& input, bool example)
{
	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		smatch match;

		if (regex_search(line, match, regex("([a-z-]+)-([0-9]+)\\[([a-z]+)\\]")))
		{
			string name = match[1];
			int id = stoi(match[2]);
			string checksum = match[3];

			if (calculateChecksum(name) == checksum)
			{
        for (char& c : name)
        {
          if (c == '-') { c = ' '; }
          else
          {
            c = ((c - 'a' + id) % 26) + 'a';
          }
        }

        if (name == "northpole object storage")
        { return to_string(id); }
			}
		}
	}

	return "Storage not found";
}
