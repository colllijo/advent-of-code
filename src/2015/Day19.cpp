#include "2015/Day19.hpp"

#include <cstdio>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

Day19_2015::Day19_2015()
{
	exampleInput =
	    "e => H\n"
	    "e => O\n"
	    "H => HO\n"
	    "H => OH\n"
	    "O => HH\n"
	    "\n"
	    "HOHOHO\n";
}

string Day19_2015::part1(const string& input, bool example)
{
	unordered_set<string> molecules;

	vector<pair<string, string>> conversions;
	string molecule;

	bool readingConversions = true;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.empty())
		{
			readingConversions = false;
			continue;
		}

		if (readingConversions)
		{
			stringstream conversion(line);
			string from, to, arrow;
			conversion >> to >> arrow >> from;
			conversions.push_back({from, to});
		}
		else
		{
			molecule = line;
		}
	}

	for (auto& [from, to] : conversions)
	{
		size_t pos = 0;
		while ((pos = molecule.find(to, pos)) != string::npos)
		{
			string newMolecule = molecule;
			newMolecule.replace(pos, to.size(), from);
			molecules.insert(newMolecule);
			pos += to.size();
		}
	}

	return to_string(molecules.size());
}

// Solution for part 2 based on https://www.happycoders.eu/algorithms/advent-of-code-2015/
string Day19_2015::part2(const string& input, bool example)
{
	string molecule;

	bool readingConversions = true;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		if (line.empty())
		{
			readingConversions = false;
			continue;
		}

		if (!readingConversions)
		{
			molecule = line;
		}
	}

	int molecules = 0;
	for (size_t i = 0; i < molecule.size(); i++)
	{
		if (isupper(molecule[i]))
		{
			molecules++;
		}

		if (molecule.substr(i).starts_with("Rn") || molecule.substr(i).starts_with("Ar"))
		{
			molecules--;
		}
		else if (molecule[i] == 'Y')
		{
			molecules -= 2;
		}
	}
	molecules--;

	return to_string(molecules);
}
