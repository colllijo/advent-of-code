#include "2015/Day20.hpp"

#include <vector>

Day20_2015::Day20_2015() { exampleInput = ""; }

string Day20_2015::part1(const string& input, bool example)
{
	int target = stoi(input) / 10;
	int houseNumber = target;

	vector<int> houses(target, 0);

	for (int i = 1; i < target; i++)
		for (int j = i; j < target; j += i)
			if ((houses[j] += i) >= target && j < houseNumber) houseNumber = j;

	return to_string(houseNumber);
}

string Day20_2015::part2(const string& input, bool example) {
	int target = stoi(input);
	int houseNumber = target;

	vector<int> houses(target, 0);

	for (int i = 1; i < target; i++)
		for (int j = i; j < target && j <= i * 50; j += i)
			if ((houses[j] += i * 11) >= target && j < houseNumber) houseNumber = j;

	return to_string(houseNumber);
}
