#pragma once

#include <map>
#include <memory>

#include "AoCDay.hpp"
#include "AoCInput.hpp"
#include "AoCSelector.hpp"
#include "AoCSubmitter.hpp"
#include "AoCYear.hpp"

class AoCRunner
{
public:
	AoCRunner();
	~AoCRunner();

	void addYear(int year, const AoCYear &aocYear);

	int run(int argc, char *argv[]);

private:
	std::map<int, AoCYear> years;
	AoCSelector selector;
	AoCInput aocInput;
	AoCSubmitter aocSubmitter;
	AoCIO& aocIO;

	bool runExamples;

	void parseArgs(int argc, char *argv[]);
	int parseArgToInt(const char *option, char *arg);
	void validateAoCSelector();

	void runPart(const std::shared_ptr<AoCDay> &aocDay, int year, int day, int part, bool example = false);

	void printVersion();
	void printHelp();
};
