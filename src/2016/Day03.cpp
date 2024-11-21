#include "2016/Day03.hpp"

#include <sstream>
#include <vector>

Day03_2016::Day03_2016()
{
	exampleInput =
	    "101 301 501\n"
	    "102 302 502\n"
	    "103 303 503\n"
	    "201 401 601\n"
	    "202 402 602\n"
	    "203 403 603\n";
}

string Day03_2016::part1(const string& input, bool example)
{
	int count = 0;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		int a, b, c;
		stringstream lineStream(line);
		lineStream >> a >> b >> c;
		if (a + b > c && a + c > b && b + c > a)
		{
			count++;
		}
	}

	return to_string(count);
}

string Day03_2016::part2(const string& input, bool example)
{
	int count = 0;

	vector<vector<int>> triangles(3, vector<int>(3));
	stringstream stream(input);
	string line;
	for (int i = 0; getline(stream, line); i++)
	{
		stringstream lineStream(line);
		lineStream >> triangles[0][i % 3] >> triangles[1][i % 3] >> triangles[2][i % 3];

		if (i % 3 == 2)
		{
			for (int c = 0; c < 3; c++)
			{
				if (triangles[c][0] + triangles[c][1] > triangles[c][2] && triangles[c][0] + triangles[c][2] > triangles[c][1] &&
				    triangles[c][2] + triangles[c][1] > triangles[c][0])
				{
					count++;
				}
			}
		}
	}

	return to_string(count);
}
