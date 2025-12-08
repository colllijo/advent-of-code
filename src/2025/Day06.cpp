#include "2025/Day06.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <ranges>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Grid.hpp"

Day06_2025::Day06_2025()
{
	exampleInput = "123 328  51 64 \n"
				   " 45 64  387 23 \n"
				   "  6 98  215 314\n"
				   "*   +   *   +";
}

string Day06_2025::part1(const string &input, bool example)
{
	std::vector<std::string> lines = caoc::strings::split(input, "\n");

	std::vector<std::string> operations =
		std::ranges::to<std::vector<std::string>>(lines[lines.size() - 1] | std::views::split(' ') | std::views::filter([](auto &&part) { return !part.empty(); }) |
												  std::views::transform([](auto &&part) { return std::ranges::to<std::string>(part); }));

	std::vector<std::int64_t> results = std::ranges::to<std::vector<std::int64_t>>(operations | std::views::transform([](auto &&operation) { return operation == "*" ? 1 : 0; }));

	lines.pop_back(); // Remove operations
	for (const auto &line : lines)
	{
		std::vector<std::int64_t> values =
			std::ranges::to<std::vector<std::int64_t>>(line | std::views::split(' ') | std::views::filter([](auto &&part) { return !part.empty(); }) |
													   std::views::transform([](auto &&part) { return std::stoll(std::ranges::to<std::string>(part)); }));

		for (std::size_t i = 0; i < results.size(); ++i)
		{
			if (operations[i] == "*") { results[i] *= values[i]; }
			else {
				results[i] += values[i];
			}
		}
	}

	return std::to_string(std::ranges::fold_left(results, 0, std::plus{}));
}

string Day06_2025::part2(const string &input, bool example)
{
	caoc::structs::Grid<char> values(input.substr(0, input.find_last_of('\n')));

	std::vector<std::string> operations = std::ranges::to<std::vector<std::string>>(input.substr(input.find_last_of('\n') + 1) | std::views::split(' ') |
																					std::views::filter([](auto &&part) { return !part.empty(); }) |
																					std::views::transform([](auto &&part) { return std::ranges::to<std::string>(part); }));

	std::vector<std::int64_t> results = std::ranges::to<std::vector<std::int64_t>>(operations | std::views::transform([](auto &&operation) { return operation == "*" ? 1 : 0; }));

	int opCounter = 0;
	for (const auto &column : values.columns())
	{
		std::string value = std::ranges::to<std::string>(column | std::views::filter([](auto &&chr) { return chr != ' '; }));

		if (value.empty())
		{
			opCounter++;
			continue;
		}

		if (operations[opCounter] == "*") { results[opCounter] *= std::stoll(value); }
		else {
			results[opCounter] += std::stoll(value);
		}
	}

	return std::to_string(std::ranges::fold_left(results, 0, std::plus{}));
}
