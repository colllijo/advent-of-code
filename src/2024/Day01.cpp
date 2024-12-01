#include "2024/Day01.hpp"

#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <vector>

Day01_2024::Day01_2024(){exampleInput =
                             "3   4\n"
                             "4   3\n"
                             "2   5\n"
                             "1   3\n"
                             "3   9\n"
                             "3   3";

}

string Day01_2024::part1(const string& input, bool example)
{
	int sum = 0;

	vector<int> left;
	vector<int> right;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		stringstream lineStream(line);
		string leftStr;
		string rightStr;

		lineStream >> leftStr >> rightStr;

		left.push_back(stoi(leftStr));
		right.push_back(stoi(rightStr));
	}

	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	for (int i = 0; i < left.size(); i++)
	{
		sum += abs(left[i] - right[i]);
	}

	return to_string(sum);
}

string Day01_2024::part2(const string& input, bool example) {
	int sum = 0;

	vector<int> left;
	unordered_map<int, int> right;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		stringstream lineStream(line);
		string leftStr;
		string rightStr;

		lineStream >> leftStr >> rightStr;

		left.push_back(stoi(leftStr));
		if (!right.count(stoi(rightStr)))
		{
			right[stoi(rightStr)] = 1;
		}
		else {
			right[stoi(rightStr)]++;
		}
	}

	sort(left.begin(), left.end());

	for (int i = 0; i < left.size(); i++)
	{
		sum += left[i] * right[left[i]];
	}

	return to_string(sum);
}
