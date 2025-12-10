#include "2025/Day08.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <unordered_map>
#include <vector>

#include "coll-aoc-runner/structs/Vector3.hpp"

Day08_2025::Day08_2025()
{
	exampleInput = "162,817,812\n"
				   "57,618,57\n"
				   "906,360,560\n"
				   "592,479,940\n"
				   "352,342,300\n"
				   "466,668,158\n"
				   "542,29,236\n"
				   "431,825,988\n"
				   "739,650,466\n"
				   "52,470,668\n"
				   "216,146,977\n"
				   "819,987,18\n"
				   "117,168,530\n"
				   "805,96,715\n"
				   "346,949,466\n"
				   "970,615,88\n"
				   "941,993,340\n"
				   "862,61,35\n"
				   "984,92,344\n"
				   "425,690,689";
}

using caoc::structs::Vector3;

typedef struct JunctionBox
{
	Vector3<std::uint64_t> position;
	std::size_t circuit;
} JunctionBox;

string Day08_2025::part1(const string &input, bool example)
{
	std::vector<JunctionBox> junctionBoxes = std::ranges::to<std::vector<JunctionBox>>(std::views::zip_transform(
		[](auto &&i, auto &&line)
		{
			auto nums = line | std::views::split(',') | std::views::transform([](auto numStr) { return std::stoull(std::string(numStr.begin(), numStr.end())); });
			auto it	  = nums.begin();

			return JunctionBox{.position = {*it, *(++it), *(++it)}, .circuit = i};
		},
		std::views::iota(std::size_t{0}), input | std::views::split('\n')));

	std::map<std::uint64_t, std::vector<std::pair<std::size_t, std::size_t>>> distances;
	for (std::size_t i = 0; i < junctionBoxes.size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < junctionBoxes.size(); ++j)
		{
			const std::uint64_t distance = junctionBoxes[i].position.distance(junctionBoxes[j].position);

			if (distances.contains(distance)) { distances[distance].emplace_back(std::pair<std::size_t, std::size_t>{i, j}); }
			else {
				distances[distance] = {std::pair<std::size_t, std::size_t>{i, j}};
			}
		}
	}

	const std::size_t CONNECTIONS = example ? 10 : 1000;
	std::size_t connections		  = 0;
	std::size_t test			  = 0;

	for (const auto &[distance, pairs] : distances)
	{
		for (const auto &[left, right] : pairs)
		{
			if (connections == CONNECTIONS) { goto finish; }
			connections++;

			std::size_t mergeFrom = junctionBoxes[right].circuit, mergeTo = junctionBoxes[left].circuit;

			if (mergeFrom == mergeTo) { continue; }
			if (example) { std::println("{} circuits left", (junctionBoxes.size() - (++test))); }

			for (auto &junctionBox : junctionBoxes)
			{
				if (junctionBox.circuit != mergeFrom) { continue; }
				junctionBox.circuit = mergeTo;
			}
		}
	}

finish:
	std::unordered_map<std::size_t, std::size_t> circuits;
	for (const auto &box : junctionBoxes) { circuits[box.circuit]++; }

	std::vector<std::pair<std::size_t, std::size_t>> counts(circuits.begin(), circuits.end());
	std::ranges::sort(counts, [](const auto &a, const auto &b) { return a.second > b.second; });

	if (example)
	{
		for (const auto &count : counts) { std::println("{} -> {}", count.first, count.second); }
		std::println("Total circuits = {}", junctionBoxes.size() - test);
	}

	return std::to_string(counts[0].second * counts[1].second * counts[2].second);
}

string Day08_2025::part2(const string &input, bool example)
{
	std::vector<JunctionBox> junctionBoxes = std::ranges::to<std::vector<JunctionBox>>(std::views::zip_transform(
		[](auto &&i, auto &&line)
		{
			auto nums = line | std::views::split(',') | std::views::transform([](auto numStr) { return std::stoull(std::string(numStr.begin(), numStr.end())); });
			auto it	  = nums.begin();

			return JunctionBox{.position = {*it, *(++it), *(++it)}, .circuit = i};
		},
		std::views::iota(std::size_t{0}), input | std::views::split('\n')));

	std::map<std::uint64_t, std::vector<std::pair<std::size_t, std::size_t>>> distances;
	for (std::size_t i = 0; i < junctionBoxes.size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < junctionBoxes.size(); ++j)
		{
			const std::uint64_t distance = junctionBoxes[i].position.distance(junctionBoxes[j].position);

			if (distances.contains(distance)) { distances[distance].emplace_back(std::pair<std::size_t, std::size_t>{i, j}); }
			else {
				distances[distance] = {std::pair<std::size_t, std::size_t>{i, j}};
			}
		}
	}

	std::size_t test = 0;

	for (const auto &[distance, pairs] : distances)
	{
		for (const auto &[left, right] : pairs)
		{
			std::size_t mergeFrom = junctionBoxes[right].circuit, mergeTo = junctionBoxes[left].circuit;

			if (mergeFrom == mergeTo) { continue; }

			if ((junctionBoxes.size() - (++test)) == 1) { return std::to_string(junctionBoxes[left].position.x() * junctionBoxes[right].position.x()); }

			for (auto &junctionBox : junctionBoxes)
			{
				if (junctionBox.circuit != mergeFrom) { continue; }
				junctionBox.circuit = mergeTo;
			}
		}
	}

	return "Could not solve problem";
}
