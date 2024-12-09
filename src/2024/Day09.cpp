#include "2024/Day09.hpp"

#include <vector>

Day09_2024::Day09_2024() { exampleInput = "2333133121414131402"; }

string Day09_2024::part1(const string& input, bool example)
{
	vector<string> memory;

	long long id = 0;
	for (long long i = 0; i < input.size(); i++)
	{
		long long size = input[i] - '0';

		for (long long j = 0; j < size; j++)
		{
			if ((i & 0b1) == 0)
			{
				memory.push_back(to_string(id));
			}
			else
			{
				memory.push_back(".");
			}
		}

		if ((i & 0b1) == 0)
		{
			id++;
		}
	}

	size_t left = 0, right = memory.size() - 1;
	while (left < right)
	{
		while (memory[left] != ".") left++;
		while (memory[right] == ".") right--;

		if (left < right)
		{
			memory[left] = memory[right];
			memory[right] = ".";
		}
	}

	unsigned long long checksum = 0;
	for (size_t i = 0; i < memory.size(); i++)
	{
		if (memory[i] != ".")
		{
			checksum += i * stol(memory[i]);
		}
	}

	return to_string(checksum);
}

struct File
{
	size_t pos;
	size_t size;
	long long id;
};

string Day09_2024::part2(const string& input, bool example)
{
	vector<string> memory;
	vector<File> files;
	vector<pair<size_t, size_t>> gaps;

	long long id = -1;
	for (long long i = 0; i < input.size(); i++)
	{
		size_t size = input[i] - '0';

		if ((i & 0b1) == 0)
		{
			id++;
			files.push_back({memory.size(), size, id});
		}
		else
		{
			gaps.push_back({memory.size(), size});
		}

		for (long long j = 0; j < size; j++)
		{
			if ((i & 0b1) == 0)
			{
				memory.push_back(to_string(id));
			}
			else
			{
				memory.push_back(".");
			}
		}
	}

	while (files.size())
	{
		File file = files.back();
		files.pop_back();

		for (size_t i = 0; i < gaps.size(); i++)
		{
			if (gaps[i].first >= file.pos) break;

			if (gaps[i].second >= file.size)
			{
				for (size_t j = 0; j < file.size; j++)
				{
					memory[gaps[i].first + j] = to_string(file.id);
					memory[file.pos + j] = ".";
				}

				if (gaps[i].second > file.size)
				{
					gaps[i].first += file.size;
					gaps[i].second -= file.size;
				}
				else
				{
					gaps.erase(gaps.begin() + i);
				}

				break;
			}
		}
	}

	unsigned long long checksum = 0;
	for (size_t i = 0; i < memory.size(); i++)
	{
		if (memory[i] != ".")
		{
			checksum += i * stol(memory[i]);
		}
	}

	return to_string(checksum);
}
