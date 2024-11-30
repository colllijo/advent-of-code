#pragma once

#include <memory>
#include <optional>
#include <string>
#include <filesystem>

#include "cache/AoCCache.hpp"

namespace fs = std::filesystem;

class AoCCookie
{
public:
	AoCCookie(const std::shared_ptr<AoCCache> &cache);

	std::string getSession();

private:
	std::shared_ptr<AoCCache> cache;

	bool isValidSession(const std::string &session);

	std::optional<std::string> loadSessionFromBrowser();
	std::optional<std::string> loadSessionFromFirefox(const fs::path& profileDir);

	std::optional<std::string> readCookieFromSQLite(const fs::path& path);
};
