#pragma once

#include <filesystem>
#include <string>

class AoCInput
{
public:
	AoCInput();
	~AoCInput();

	std::string getInput(int year, int day);

private:
	std::filesystem::path inputDir;
	std::string authCookie;

	void loadAuthCookie();
	void downloadInput(int year, int day);
};
