#include "strings/Format.hpp"

#include <ranges>
#include <vector>

namespace caoc::strings
{
	std::string trim(const std::string& str, const std::string whitespace)
	{
		const auto strBegin = str.find_first_not_of(whitespace);
		const auto strEnd = str.find_last_not_of(whitespace);
		if (strBegin == std::string::npos) return "";

		return str.substr(strBegin, strEnd - strBegin + 1);
	}

	std::vector<std::string> split(const std::string& str, const std::string delimiter)
	{
		std::vector<std::string> result;
		auto split_view = str | std::views::split(delimiter);

		for (const auto& part : split_view)
		{
			result.emplace_back(part.begin(), part.end());
		}

		return result;
	}
};  // namespace caoc::strings
