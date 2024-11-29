#pragma once

#include <string>

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

	void printPartResult(int year, int day, int part, const std::string& result, bool example);
	void printFullPartResult(int year, int day, int part, const std::string& result, const std::string& exampleResult);
	void printSolveState(AoCSolveState state, bool cached = false);

private:
	AoCIO() = default;
	AoCIO(const AoCIO&) = delete;
	AoCIO& operator=(const AoCIO&) = delete;

	char getChar();
};
