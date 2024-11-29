#include "2016/Day09.hpp"

#include <regex>
#include <sstream>

Day09_2016::Day09_2016()
{
	exampleInput = "X(8x2)(3x3)ABCY";
}

unsigned long decompress(string input)
{
	unsigned long size = 0;

	size_t pos = 0;
	regex pattern(R"((\((\d+)x(\d+)\)))");
	auto mBegin = sregex_iterator(input.begin(), input.end(), pattern);
	auto mEnd = sregex_iterator();

	if (mBegin == mEnd)
	{
		return input.size();
	}

	for (sregex_iterator i = mBegin; i != mEnd; ++i)
	{
		smatch match = *i;
		if (match.position() < pos)
		{
			continue;
		}

		int length = stoi(match.str().substr(1, match.str().find('x') - 1));
		int reps = stoi(match.str().substr(match.str().find('x') + 1));

		size += match.position() - pos + reps * length;
		pos = match.position() + match.str().size() + length;
	}

	size += input.size() - pos;

	return size;
}

string Day09_2016::part1(const string& input, bool example)
{
	int length = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		length += decompress(line);
	}

	return to_string(length);
}

unsigned long recursiveDecompress(const std::string& input)
{
	unsigned long size = 0;

	size_t pos = 0;
	regex pattern(R"((\((\d+)x(\d+)\)))");
	auto mBegin = sregex_iterator(input.begin(), input.end(), pattern);
	auto mEnd = sregex_iterator();

	printf("%s\n", input.c_str());
	if (mBegin == mEnd)
	{
		return input.size();
	}

	for (sregex_iterator i = mBegin; i != mEnd; ++i)
	{
		smatch match = *i;
		if (match.position() < pos)
		{
			continue;
		}

		int length = stoi(match.str().substr(1, match.str().find('x') - 1));
		int reps = stoi(match.str().substr(match.str().find('x') + 1));

		size += input.substr(pos, match.position() - pos).size();
		size += reps * recursiveDecompress(input.substr(match.position() + match.str().size(), length));

		pos = match.position() + match.str().size() + length;
	}

	size += input.substr(pos).size();

	return size;
}

string Day09_2016::part2(const string& input, bool example)
{
	unsigned long length = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		length += recursiveDecompress(line);
		break;
	}

	return to_string(length);
}
