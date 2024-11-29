#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

#include "AoCLocalCache.hpp"

class AoCCache
{
public:
	explicit AoCCache();
	explicit AoCCache(const std::string& filename);

	~AoCCache();

	std::optional<std::string> get(const std::string& key);
	void set(const std::string& key, const std::string& value);
	void unset(const std::string& key);
	void clear();

private:
	bool inMemory;
	std::unique_ptr<AoCLocalCache> localCache;

	std::unordered_map<std::string, std::string> cache;
};
