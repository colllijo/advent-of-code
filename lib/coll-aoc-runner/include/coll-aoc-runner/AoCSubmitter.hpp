#pragma once

#include <filesystem>
#include <memory>
#include <tuple>

#include "cache/AoCCache.hpp"
#include "AoCStructs.hpp"
#include "AoCIO.hpp"

class AoCSubmitter
{
public:
	AoCSubmitter();
	~AoCSubmitter();

	std::tuple<AoCSolveState, bool> submit(int year, int day, int part, const std::string &answer);
private:
	std::filesystem::path cacheDir;
	std::unique_ptr<AoCCache> cache;

	AoCIO& aocIO;

	std::string authCookie;

	void loadAuthCookie();
	AoCSolveState submitAnswer(int year, int day, int part, const std::string &answer);
};
