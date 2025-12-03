#pragma once

#include <string>
#include <chrono>

#include "AoCStructs.hpp"

class AoCIO
{
public:
	static AoCIO& getInstance()
	{
		static AoCIO instance;
		return instance;
	}

	bool getConfirmation(const std::string& prompt, bool defaultAnswer = false);

	void printPartResult(int year, int day, int part, const std::string& result, const std::chrono::high_resolution_clock::duration &duration, bool example);
	void printFullPartResult(int year, int day, int part, const std::string& result, const std::string& exampleResult, const std::chrono::high_resolution_clock::duration &duration,  const std::chrono::high_resolution_clock::duration &exampleDuration);
	void printSolveState(AoCSolveState state, bool cached = false);

  void printError(const std::string& error);

private:
	AoCIO() = default;
	AoCIO(const AoCIO&) = delete;
	AoCIO& operator=(const AoCIO&) = delete;

	char getChar();
};
