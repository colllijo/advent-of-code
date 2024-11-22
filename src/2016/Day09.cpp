#include "2016/Day09.hpp"

#include <regex>
#include <sstream>

Day09_2016::Day09_2016()
{
	exampleInput =
	    "ADVENT\n"
	    "A(1x5)BC\n"
	    "(3x3)XYZ\n"
	    "A(2x2)BCD(2x2)EFG\n"
	    "(6x1)(1x3)A\n"
	    "X(8x2)(3x3)ABCY\n";
}

string decompress(string input, bool recursive = false)
{
	string decompressed = "";

	size_t pos = 0;
	regex pattern(R"((\((\d+)x(\d+)\)))");
	auto mBegin = sregex_iterator(input.begin(), input.end(), pattern);
	auto mEnd = sregex_iterator();

  if (mBegin == mEnd)
  {
    return input;
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
		string toRepeat = input.substr(match.position() + match.str().size(), length);

		decompressed += input.substr(pos, match.position() - pos);
		for (int i = 0; i < reps; i++)
		{
			decompressed += toRepeat;
		}

		pos = match.position() + match.str().size() + length;
	}

	decompressed += input.substr(pos);

  if (recursive)
  {
    return decompress(decompressed, true);
  }

	return decompressed;
}

string Day09_2016::part1(const string& input, bool example)
{
	int length = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		length += decompress(line).size();
	}

	return to_string(length);
}

string Day09_2016::part2(const string& input, bool example)
{
	unsigned long length = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		string decompressed = "";

		length += decompress(line, true).size();
	}

	return to_string(length);
}
