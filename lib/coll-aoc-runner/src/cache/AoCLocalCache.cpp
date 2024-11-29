#include "cache/AoCLocalCache.hpp"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>

AoCLocalCache::AoCLocalCache(const std::string& filename) : filename(filename), keyHasher()
{
	std::ifstream file(filename, std::ios::binary);
	cacheExists = file.good();
}

void AoCLocalCache::save(const std::unordered_map<std::string, std::string>& cache)
{
	if (!cacheExists)
	{
		createCache(cache);
	}
	else
	{
		patchCache(cache);
	}
}

void AoCLocalCache::clear()
{
	lookupTable.clear();
	std::remove(filename.c_str());
}

void AoCLocalCache::createCache(const std::unordered_map<std::string, std::string>& cache)
{
	std::ofstream file(filename, std::ios::binary | std::ios::trunc);
	if (!file.is_open()) throw std::ios_base::failure("Failed to open cache file to save data");

	const size_t metadataSize = 2 * sizeof(size_t);

	char buffer[metadataSize];
	std::memset(buffer, 0, metadataSize);
	file.write(reinterpret_cast<const char*>(buffer), metadataSize);

	// Write data
	size_t dataOffset = file.tellp();

	for (const auto& [key, value] : cache)
	{
		lookupTable[keyHasher(key)] = file.tellp();

		size_t keySize = key.size();
		size_t valueSize = value.size();

		file.write(reinterpret_cast<const char*>(&keySize), sizeof(keySize));
		file.write(reinterpret_cast<const char*>(&valueSize), sizeof(valueSize));
		file.write(key.c_str(), keySize);
		file.write(value.c_str(), valueSize);
	}

	// Write lookup table to find data offset by hash
	size_t lookupTableOffset = file.tellp();

	for (const auto& [hash, offset] : lookupTable)
	{
		file.write(reinterpret_cast<const char*>(&hash), sizeof(hash));
		file.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
	}

	// Write metadata to find the sections of the file
	file.seekp(0, std::ios::beg);
	file.write(reinterpret_cast<const char*>(&dataOffset), sizeof(dataOffset));
	file.write(reinterpret_cast<const char*>(&lookupTableOffset), sizeof(lookupTableOffset));
}

void AoCLocalCache::patchCache(const std::unordered_map<std::string, std::string>& cache)
{
	if (!lookupTableLoaded) loadLookupTable();

	std::unordered_map<std::string, std::string> fullCache = cache;

	for (const auto& [hash, _] : lookupTable)
	{
		auto entry = getByHash(hash);
		if (!entry.has_value()) continue;
		if (markedForRemoval.contains(entry->key)) continue;
		if (cache.contains(entry->key)) continue;

		fullCache[entry->key] = entry->value;
	}

	clear();
	createCache(fullCache);
}

std::optional<std::string> AoCLocalCache::get(const std::string& key)
{
	if (!lookupTableLoaded) loadLookupTable();

	auto data = getByHash(keyHasher(key));
	if (data.has_value())
	{
		return data->value;
	}
	return std::nullopt;
}

std::optional<AoCLocalCache::DataEntry> AoCLocalCache::getByHash(const size_t key)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file) return std::nullopt;

	if (!lookupTable.contains(key)) return std::nullopt;

	file.seekg(lookupTable.at(key), std::ios::beg);

	DataEntry data;

	file.read(reinterpret_cast<char*>(&data.keySize), sizeof(data.keySize));
	file.read(reinterpret_cast<char*>(&data.valueSize), sizeof(data.valueSize));

	data.key.resize(data.keySize, '\0');
	data.value.resize(data.valueSize, '\0');
	file.read(reinterpret_cast<char*>(data.key.data()), data.keySize);
	file.read(reinterpret_cast<char*>(data.value.data()), data.valueSize);

	return data;
}

void AoCLocalCache::unset(const std::string& key) { markedForRemoval.insert(key); }

void AoCLocalCache::loadLookupTable()
{
	std::ifstream file(filename, std::ios::binary);
	if (!file) return;

	lookupTableLoaded = true;

	size_t fileSize, lookupTableOffset;

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();

	file.seekg(sizeof(size_t), std::ios::beg);
	file.read(reinterpret_cast<char*>(&lookupTableOffset), sizeof(lookupTableOffset));

	file.seekg(lookupTableOffset, std::ios::beg);
	while (static_cast<int>(file.tellg()) + static_cast<int>(sizeof(LookupTableEntry)) <= fileSize)
	{
		LookupTableEntry entry;
		file.read(reinterpret_cast<char*>(&entry), sizeof(entry));

		lookupTable[entry.hash] = entry.offset;
	}
}
