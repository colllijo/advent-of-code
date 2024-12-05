#include "2024/Day04.hpp"

#include <sstream>
#include <vector>

#include "coll-aoc-runner/structs/Grid.hpp"

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
	int count = 0;
	caoc::structs::Grid<char> grid(input);

	for (const auto& row : grid.rows())
	{
		for (int i = 0; i < row.size() - 3; i++)
		{
			if ((row[i] == 'X' && row[i + 1] == 'M' && row[i + 2] == 'A' && row[i + 3] == 'S') || (row[i] == 'S' && row[i + 1] == 'A' && row[i + 2] == 'M' && row[i + 3] == 'X'))
			{
				count++;
			}
		}
	}

	for (const auto& column : grid.columns())
	{
		for (int i = 0; i < column.size() - 3; i++)
		{
			if ((column[i] == 'X' && column[i + 1] == 'M' && column[i + 2] == 'A' && column[i + 3] == 'S') ||
			    (column[i] == 'S' && column[i + 1] == 'A' && column[i + 2] == 'M' && column[i + 3] == 'X'))
			{
				count++;
			}
		}
	}

	for (const auto& diagonal : grid.diagonals())
	{
		if (diagonal.size() < 3) continue;

		for (int i = 0; i < diagonal.size() - 3; i++)
		{
			if ((diagonal[i] == 'X' && diagonal[i + 1] == 'M' && diagonal[i + 2] == 'A' && diagonal[i + 3] == 'S') ||
			    (diagonal[i] == 'S' && diagonal[i + 1] == 'A' && diagonal[i + 2] == 'M' && diagonal[i + 3] == 'X'))
			{
				count++;
			}
		}
	}

	return to_string(count);
}

string Day04_2024::part2(const string& input, bool example)
{
	long long count = 0;
  caoc::structs::Grid<char> grid(input);

	for (int y = 0; y < grid.height() - 2; y++)
	{
		for (int x = 0; x < grid.width() - 2; x++)
		{
			if (grid(x + 1, y + 1) != 'A') continue;

			int crossCount = 0;

      if (grid(x, y) == 'M' && grid(x + 2, y + 2) == 'S') crossCount++;
      if (grid(x, y) == 'S' && grid(x + 2, y + 2) == 'M') crossCount++;
      if (grid(x + 2, y) == 'M' && grid(x, y + 2) == 'S') crossCount++;
      if (grid(x + 2, y) == 'S' && grid(x, y + 2) == 'M') crossCount++;

			if (crossCount >= 2) count++;
		}
	}

	return to_string(count);
}
