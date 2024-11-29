#include "AoCRunner.hpp"

#include <getopt.h>

#include <cstdlib>
#include <cwchar>
#include <string>

#include "AoCDay.hpp"

AoCRunner::AoCRunner() : runExamples(true), aocIO(AoCIO::getInstance()) {}
AoCRunner::~AoCRunner() = default;

void AoCRunner::addYear(int year, const AoCYear &aocYear) { years[year] = aocYear; }

int AoCRunner::run(int argc, char *argv[])
{
	parseArgs(argc, argv);

	for (const auto &[year, aocYear] : years)
	{
		if (selector.year != -1 && selector.year != year) continue;

		for (auto &[day, aocDay] : aocYear.getDays())
		{
			if (selector.day != -1 && selector.day != day) continue;

			if (selector.part != 2) runPart(aocDay, year, day, 1, runExamples);
			if (selector.part != 1) runPart(aocDay, year, day, 2, runExamples);
		}
	}

	return 0;
}

void AoCRunner::runPart(const std::shared_ptr<AoCDay> &aocDay, int year, int day, int part, bool example)
{
	std::string result;
	std::string input = aocInput.getInput(year, day);
	bool solved = false;

	std::string exampleResult;
	std::string exampleInput = aocDay->getExampleInput();
	bool exampleSolved = false;

	if (example && !exampleInput.empty())
		exampleResult = part == 1 ? aocDay->part1(exampleInput, true) : aocDay->part2(exampleInput, true);
	result = part == 1 ? aocDay->part1(input) : aocDay->part2(input);

	solved = !result.empty() && !result.starts_with("TODO");
	exampleSolved = !exampleResult.empty() && !exampleResult.starts_with("TODO");

	if (solved && exampleSolved) aocIO.printFullPartResult(year, day, part, result, exampleResult);
	else if (solved) aocIO.printPartResult(year, day, part, result, false);
	else if (exampleSolved) aocIO.printPartResult(year, day, part, exampleResult, true);

	if (!solved) return;

	auto [state, cached] = aocSubmitter.submit(year, day, part, result);
	aocIO.printSolveState(state, cached);
}

void AoCRunner::parseArgs(int argc, char *argv[])
{
	const struct option longopts[] = {{"help", no_argument, nullptr, 'h'},
	                                  {"version", no_argument, nullptr, 'v'},
	                                  {"year", required_argument, nullptr, 'y'},
	                                  {"day", required_argument, nullptr, 'd'},
	                                  {"part", required_argument, nullptr, 'p'},
	                                  {"no-example", no_argument, nullptr, 'x'},
	                                  {nullptr, 0, nullptr, 0}};

	int opt;
	while ((opt = getopt_long(argc, argv, "hvy:d:p:", longopts, nullptr)) != -1)
	{
		switch (opt)
		{
			case 'h':
			case 'v':
				opt == 'h' ? printHelp() : printVersion();
				exit(0);
			case 'y':
				selector.year = parseArgToInt("year", optarg);
				break;
			case 'd':
				selector.day = parseArgToInt("day", optarg);
				break;
			case 'p':
				selector.part = parseArgToInt("part", optarg);
				break;
			case 'x':
				runExamples = false;
				break;
			case '?':
				fprintf(stderr, "\033[91mError:\033[0m Bad argument\n");
				exit(1);
			default:
				abort();
		}
	}

	validateAoCSelector();
}

int AoCRunner::parseArgToInt(const char *option, char *arg)
{
	try
	{
		return std::stoi(arg);
	}
	catch (std::invalid_argument &e)
	{
		fprintf(stderr, "\033[91mError:\033[0m Invalid argument for option %s, (%s)\n", option, arg);
	}
	catch (std::out_of_range &e)
	{
		fprintf(stderr, "\033[91mError:\033[0m Argument out of range for option %s (%s)\n", option, arg);
	}

	exit(1);
}

void AoCRunner::validateAoCSelector()
{
	if (selector.year != -1 && selector.year < 2015)
	{
		fprintf(stderr, "\033[91mError:\033[0m Invalid year %d\n", selector.year);
		exit(1);
	}
	if (selector.day != -1 && (selector.day < 1 || selector.day > 25))
	{
		fprintf(stderr, "\033[91mError:\033[0m Invalid day %d\n", selector.day);
		exit(1);
	}
	if (selector.part != -1 && (selector.part < 1 || selector.part > 2))
	{
		fprintf(stderr, "\033[91mError:\033[0m Invalid part %d\n", selector.part);
		exit(1);
	}
}

void AoCRunner::printVersion() { printf("Advent of Code Runner v0.1\n"); }

void AoCRunner::printHelp() { printf("Usage: aoc-runner [options]\n"); }
