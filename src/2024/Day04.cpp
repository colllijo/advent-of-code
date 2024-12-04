#include "2024/Day04.hpp"

#include <sstream>
#include <vector>

Day04_2024::Day04_2024()
{
	exampleInput =
	    "MMMSXXMASM\n"
	    "MSAMXMSMSA\n"
	    "AMXSXMAAMM\n"
	    "MSAMASMSMX\n"
	    "XMASAMXAMM\n"
	    "XXAMMXXAMA\n"
	    "SMSMSASXSS\n"
	    "SAXAMASAAA\n"
	    "MAMMMXMMMM\n"
	    "MXMXAXMASX";
}

std::vector<std::vector<char>> rotate90Degrees(const std::vector<std::vector<char>>& matrix)
{
	int rows = matrix.size();
	int cols = matrix[0].size();
	std::vector<std::vector<char>> rotated(cols, std::vector<char>(rows));

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			rotated[j][i] = matrix[i][j];
		}
	}

	return rotated;
}

string Day04_2024::part1(const string& input, bool example)
{
	long long count = 0;
	vector<vector<char>> grid;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		vector<char> row;

		for (char c : line)
		{
			row.push_back(c);
		}
		grid.push_back(row);
	}

	for (auto row : grid)
	{
		for (int i = 0; i < row.size() - 3; i++)
		{
			if ((row[i] == 'X' && row[i + 1] == 'M' && row[i + 2] == 'A' && row[i + 3] == 'S') || (row[i] == 'S' && row[i + 1] == 'A' && row[i + 2] == 'M' && row[i + 3] == 'X'))
			{
				count++;
			}
		}
	}

	vector<vector<char>> rotated = rotate90Degrees(grid);

	for (auto row : rotated)
	{
		for (int i = 0; i < row.size() - 3; i++)
		{
			if ((row[i] == 'X' && row[i + 1] == 'M' && row[i + 2] == 'A' && row[i + 3] == 'S') ||
				(row[i] == 'S' && row[i + 1] == 'A' && row[i + 2] == 'M' && row[i + 3] == 'X'))
			{
				count++;
			}
		}
	}

    for (int i = 0; i < grid.size() - 3; i++) {
        for (int j = 0; j < grid[i].size() - 3; j++) {
            if ((grid[i][j] == 'X' && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S')
                || (grid[i][j] == 'S' && grid[i + 1][j + 1] == 'A' && grid[i + 2][j + 2] == 'M' && grid[i + 3][j + 3] == 'X')) {
                count++;
            }
        }
    }

    for (int i = 3; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size() - 3; j++) {
            if ((grid[i][j] == 'X' && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S')
                || (grid[i][j] == 'S' && grid[i - 1][j + 1] == 'A' && grid[i - 2][j + 2] == 'M' && grid[i - 3][j + 3] == 'X')) {
                count++;
            }
        }
    }

	return to_string(count);
}

string Day04_2024::part2(const string& input, bool example)
{
	long long count = 0;
	vector<vector<char>> grid;

	stringstream stream(input);
	string line;
	while (getline(stream, line))
	{
		vector<char> row;

		for (char c : line)
		{
			row.push_back(c);
		}
		grid.push_back(row);
	}

	for (int i = 0; i < grid.size() - 2; i++)
	{
		for (int j = 0; j < grid[i].size() - 2; j++)
		{
			if (grid[i + 1][j +  1] != 'A') continue;

			int crossCount = 0;

			if (grid[i][j] == 'M' && grid[i + 2][j + 2] == 'S') crossCount++;
			if (grid[i][j] == 'S' && grid[i + 2][j + 2] == 'M') crossCount++;
			if (grid[i + 2][j] == 'M' && grid[i][j + 2] == 'S') crossCount++;
			if (grid[i + 2][j] == 'S' && grid[i][j + 2] == 'M') crossCount++;

			if (crossCount >= 2)
			{
				if (!example) printf("%d, %d\n", i, j);
				count++;
			}
		}
	}

	return to_string(count);
}
