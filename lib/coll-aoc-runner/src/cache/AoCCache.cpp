#include "cache/AoCCache.hpp"

AoCCache::AoCCache() : inMemory(true), localCache(nullptr) {}
AoCCache::AoCCache(const std::string& filename) : inMemory(false), localCache(std::make_unique<AoCLocalCache>(filename)) {}

AoCCache::~AoCCache()
{
	if (!inMemory)
	{
		localCache->save(cache);
	}
}

std::optional<std::string> AoCCache::get(const std::string& key)
{
	if (cache.find(key) != cache.end()) return cache.at(key);

	if (inMemory) return std::nullopt;

	auto value = localCache->get(key);
	if (value.has_value()) cache[key] = value.value();

	return value;
}

void AoCCache::set(const std::string& key, const std::string& value) { cache[key] = value; }

void AoCCache::unset(const std::string& key)
{
	cache.erase(key);

	if (!inMemory)
	{
		localCache->unset(key);
	}
}

void AoCCache::clear()
{
	cache.clear();
	localCache->clear();
}
