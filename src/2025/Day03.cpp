#include "2025/Day03.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <ranges>
#include <string_view>
#include <vector>

Day03_2025::Day03_2025()
{
	exampleInput =
	    "987654321111111\n"
	    "811111111111119\n"
	    "234234234234278\n"
	    "818181911112111";
}

std::uint64_t getJoltage(const std::string_view batteryData, std::size_t batteryCount)
{
	std::uint64_t joltage = 0;
	std::array<std::vector<std::string_view::size_type>, 9> batteryCharges = {};

	// Pre allocate space in each charge vector
	for (auto& vec : batteryCharges) { vec.reserve(batteryData.size()); }

	for (std::string_view::size_type i = 0; i < batteryData.size(); ++i) { batteryCharges[batteryData[i] - '1'].emplace_back(i); }

	std::size_t nextAvailableIndex = 0;
	for (std::size_t currentBattery = 0; currentBattery < batteryCount; ++currentBattery)
	{
		std::size_t lastAllowedIndex = batteryData.size() - (batteryCount - 1 - currentBattery);
		for (std::array<std::vector<std::string_view::size_type>, 9>::size_type charge = 9; charge > 0; --charge)
		{
			for (const auto& batteryIndex : batteryCharges[charge - 1])
			{
				if (batteryIndex < nextAvailableIndex) { continue; }
				if (batteryIndex >= lastAllowedIndex) { continue; }

				nextAvailableIndex = batteryIndex + 1;
				joltage = (10 * joltage) + charge;

				goto nextBattery;
			}

			continue;

		nextBattery:
			break;
		}
	}

	return joltage;
}

string Day03_2025::part1(const string& input, bool example)
{
	return std::to_string(std::ranges::fold_left(std::views::split(input, '\n') | std::views::filter([](const auto& line) { return !line.empty(); }) |
	                                                 std::views::transform([&](const auto& line) { return getJoltage(std::string_view(line), 2); }),
	    0, std::plus{}));
}

string Day03_2025::part2(const string& input, bool example)
{
	return std::to_string(std::ranges::fold_left(std::views::split(input, '\n') | std::views::filter([](const auto& line) { return !line.empty(); }) |
	                                                 std::views::transform([&](const auto& line) { return getJoltage(std::string_view(line), 12); }),
	    0, std::plus{}));
}
