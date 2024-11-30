#pragma once

#include <memory>
#include <tuple>

#include "AoCCookie.hpp"
#include "cache/AoCCache.hpp"
#include "AoCStructs.hpp"
#include "AoCIO.hpp"

class AoCSubmitter
{
public:
	AoCSubmitter(const std::shared_ptr<AoCCache>& aocCache, const std::shared_ptr<AoCCookie>& aocCookie);
	~AoCSubmitter();

	std::tuple<AoCSolveState, bool> submit(int year, int day, int part, const std::string &answer);
private:
	std::shared_ptr<AoCCache> cache;
	std::shared_ptr<AoCCookie> cookie;

	AoCIO& aocIO;

	AoCSolveState submitAnswer(int year, int day, int part, const std::string &answer);
};
