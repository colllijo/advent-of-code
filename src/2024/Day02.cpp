#include "2024/Day02.hpp"

#include <sstream>
#include <vector>

Day02_2024::Day02_2024()
{
	exampleInput =
	    "7 6 4 2 1\n"
	    "1 2 7 8 9\n"
	    "9 7 6 2 1\n"
	    "1 3 2 4 5\n"
	    "8 6 4 4 1\n"
	    "1 3 6 7 9";
}

bool isSafe(vector<int> nums)
{
	bool safe = true;
	bool increasing = nums[0] < nums[1];
	for (int i = 0; i < nums.size() - 1 && safe; i++)
	{
		int diff = nums[i + 1] - nums[i];
		if (1 > abs(diff) || abs(diff) > 3) safe = false;
		if (increasing && diff < 0) safe = false;
		if (!increasing && diff > 0) safe = false;
	}

	return safe;
};

string Day02_2024::part1(const string& input, bool example)
{
	int sum = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		vector<int> numbers;

		stringstream lineStream(line);
		string token;
		while (getline(lineStream, token, ' '))
		{
			numbers.push_back(stoi(token));
		}

		if (isSafe(numbers)) sum++;
	}

	return to_string(sum);
}

string Day02_2024::part2(const string& input, bool example)
{
	int sum = 0;
	vector<vector<int>> unsafe;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		vector<int> numbers;

		stringstream lineStream(line);
		string token;
		while (getline(lineStream, token, ' '))
		{
			numbers.push_back(stoi(token));
		}

		if (isSafe(numbers))
			sum++;
		else
			unsafe.push_back(numbers);
	}

	// Dampening
	for (const auto nums : unsafe)
	{
		for (int i = 0; i < nums.size(); i++)
		{
			vector<int> copy = nums;
			copy.erase(copy.begin() + i);

			if (isSafe(copy))
			{
				sum++;
				break;
			}
		}
	}

	return to_string(sum);
}
