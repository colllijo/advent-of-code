#pragma once

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

class AoCLocalCache
{
public:
	AoCLocalCache(const std::string& filename);

	void save(const std::unordered_map<std::string, std::string>& cache);
	void clear();

	std::optional<std::string> get(const std::string& key);
	void unset(const std::string& key);

private:
	struct LookupTableEntry {
		size_t hash;
		size_t offset;
	};

	struct DataEntry
	{
		size_t keySize;
		size_t valueSize;
		std::string key;
		std::string value;
	};

	bool cacheExists, lookupTableLoaded;
	const std::string filename;
	const std::hash<std::string> keyHasher;

	std::optional<DataEntry> getByHash(const size_t key);

	void createCache(const std::unordered_map<std::string, std::string>& cache);
	void patchCache(const std::unordered_map<std::string, std::string>& cache);

	std::map<size_t, size_t> lookupTable;
	std::unordered_set<std::string> markedForRemoval;

	void loadLookupTable();
};

/**
 * Cache file format:
 * Metadata:
 *	data_offset
 *	lookup_table_offset
 * Data:
 *	hash
 *	key_size
 *	value_size
 *	key
 *	value
 * Lookup table:
 *	hash
 *	offset
 */
