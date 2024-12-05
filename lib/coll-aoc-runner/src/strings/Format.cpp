#include "strings/Format.hpp"

namespace caoc::strings
{
  std::string trim(const std::string& str, const std::string whitespace)
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		const auto strEnd = str.find_last_not_of(whitespace);
		if (strBegin == std::string::npos) return "";

		return str.substr(strBegin, strEnd - strBegin + 1);
	}
};
