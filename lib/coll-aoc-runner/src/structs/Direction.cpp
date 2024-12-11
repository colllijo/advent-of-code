#include "structs/Direction.hpp"

#include "structs/Vector2.hpp"

namespace caoc::structs
{
	Vector2<int> Direction::direction() const
	{
		switch (m_value)
		{
			case NORTH_WEST:
				return {-1, -1};
			case NORTH:
				return {0, -1};
			case NORTH_EAST:
				return {1, -1};
			case WEST:
				return {-1, 0};
			case EAST:
				return {1, 0};
			case SOUTH_WEST:
				return {-1, 1};
			case SOUTH:
				return {0, 1};
			case SOUTH_EAST:
				return {1, 1};
			default:
				return {0, 0};
		}
	}
};  // namespace caoc::structs
