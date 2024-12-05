#pragma once

#include <array>
#include <utility>

namespace caoc::structs
{
  typedef std::pair<int, int> Point;

	class Direction
	{
	public:

		enum Value
		{
			NORTH_WEST = -9,
			NORTH = -8,
			NORTH_EAST = -7,
			WEST = -1,
			EAST = 1,
			SOUTH_WEST = 7,
			SOUTH = 8,
			SOUTH_EAST = 9
		};

		Direction() = default;
		constexpr Direction(Value value) : m_value(value) {}

    Point direction() const;

    explicit operator bool() const = delete;
		constexpr operator Value() const { return m_value; }
		constexpr bool operator==(Direction other) const { return m_value == other.m_value; }
		constexpr bool operator!=(Direction other) const { return m_value != other.m_value; }

	private:
		Value m_value;
	};

  constexpr std::array<Direction, 8> Directions = {
    Direction(Direction::NORTH_WEST),
    Direction(Direction::NORTH),
    Direction(Direction::NORTH_EAST),
    Direction(Direction::WEST),
    Direction(Direction::EAST),
    Direction(Direction::SOUTH_WEST),
    Direction(Direction::SOUTH),
    Direction(Direction::SOUTH_EAST)
  };
};  // namespace caoc::structs
