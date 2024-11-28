#pragma once

#include <type_traits>

namespace caoc
{
	namespace math
	{
    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
    modExp(T base, T exp, T mod)
    {
      T result = exp & 0b1 ? base : 1;

      while (exp >>= 1)
      {
        base = (base * base) % mod;
        if (exp & 0b1)
        {
          result = (result * base) % mod;
        }
      }

      return result;
    }
	};
};
