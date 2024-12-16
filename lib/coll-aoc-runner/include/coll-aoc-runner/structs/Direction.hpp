#pragma once

#include <array>

#include "coll-aoc-runner/structs/Vector2.hpp"

namespace caoc::structs
{
	class Direction
	{
	public:
		enum Value
		{
			NORTH_WEST,
			NORTH,
			NORTH_EAST,
      EAST,
      SOUTH_EAST,
      SOUTH,
			SOUTH_WEST,
      WEST
		};

		Direction() = default;
		constexpr Direction(Value value) : m_value(value) {}

		Vector2<int> direction() const;

    Direction& rotateLeft(int times = 2);
    Direction& rotateRight(int times = 2);

		explicit operator bool() const = delete;
		constexpr operator Value() const { return m_value; }
		constexpr bool operator==(Direction other) const { return m_value == other.m_value; }
		constexpr bool operator!=(Direction other) const { return m_value != other.m_value; }

    static Direction rotateLeft(const Direction& dir, int times = 2);
    static Direction rotateRight(const Direction& dir, int times = 2);

	private:
		Value m_value;
	};

	constexpr std::array<Direction, 4> CardinalDirections = {Direction(Direction::NORTH), Direction(Direction::WEST), Direction(Direction::EAST), Direction(Direction::SOUTH)};
	constexpr std::array<Direction, 8> Directions = {Direction(Direction::NORTH_WEST), Direction(Direction::NORTH),     Direction(Direction::NORTH_EAST),
	                                                 Direction(Direction::WEST),       Direction(Direction::EAST),      Direction(Direction::SOUTH_WEST),
	                                                 Direction(Direction::SOUTH),      Direction(Direction::SOUTH_EAST)};
};  // namespace caoc::structs
