#include "2024/Day07.hpp"
#include <sstream>
#include <vector>

Day07_2024::Day07_2024() {
	exampleInput =
"190: 10 19\n"
"3267: 81 40 27\n"
"83: 17 5\n"
"156: 15 6\n"
"7290: 6 8 6 15\n"
"161011: 16 10 13\n"
"192: 17 8 14\n"
"21037: 9 7 18 13\n"
"292: 11 6 16 20";
}

string Day07_2024::part1(const string& input, bool example) {
	long long sum = 0;

	stringstream stream(input); string line;
	while (getline(stream, line)) {
		long test;
		vector<long> numbs;

		test = stol(line.substr(0, line.find(":")));
		string num;
		stringstream ss(line.substr(line.find(":") + 2));

		while (getline(ss, num, ' ')) {
			numbs.push_back(stol(num));
		}

		vector<vector<long>> possibilities = { numbs };

		while (!possibilities.empty()) {
			vector<long> current = possibilities.back();
			possibilities.pop_back();

			if (current.size() == 1) {
				if (current[0] == test) {
					sum += test;
					possibilities.clear();
				}
				continue;
			}

			long left = current[0];
			long right = current[1];

			current.erase(current.begin());
			vector<long> add = current;
			vector<long> mul = current;

			add[0] = left + right;
			mul[0] = left * right;

			possibilities.push_back(add);
			possibilities.push_back(mul);
		}
	}

	return to_string(sum);
}

string Day07_2024::part2(const string& input, bool example) {
	long long sum = 0;

	stringstream stream(input); string line;
	while (getline(stream, line)) {
		long test;
		vector<long> numbs;

		test = stol(line.substr(0, line.find(":")));
		string num;
		stringstream ss(line.substr(line.find(":") + 2));

		while (getline(ss, num, ' ')) {
			numbs.push_back(stol(num));
		}

		vector<vector<long>> possibilities = { numbs };

		while (!possibilities.empty()) {
			vector<long> current = possibilities.back();
			possibilities.pop_back();

			if (current.size() == 1) {
				if (current[0] == test) {
					sum += test;
					possibilities.clear();
				}
				continue;
			}

			long left = current[0];
			long right = current[1];

			current.erase(current.begin());
			vector<long> add = current;
			vector<long> mul = current;
			vector<long> concat = current;

			add[0] = left + right;
			mul[0] = left * right;
			concat[0] = stol(string(to_string(left)  + to_string(right)));

			possibilities.push_back(add);
			possibilities.push_back(mul);
			possibilities.push_back(concat);
		}
	}

	return to_string(sum);
}
