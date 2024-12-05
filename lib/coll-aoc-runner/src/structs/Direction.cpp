#include "structs/Direction.hpp"

namespace caoc::structs
{
	Point Direction::direction() const
  {
    switch (m_value) {
      case NORTH_WEST: return {-1, -1};
      case NORTH: return {0, -1};
      case NORTH_EAST: return {1, -1};
      case WEST: return {-1, 0};
      case EAST: return {1, 0};
      case SOUTH_WEST: return {-1, 1};
      case SOUTH: return {0, 1};
      case SOUTH_EAST: return {1, 1};
    }
  }
};  // namespace caoc::structs
