#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "AoCCookie.hpp"

class AoCInput
{
public:
	AoCInput(const std::shared_ptr<AoCCookie>& aocCookie);
	~AoCInput();

	std::string getInput(int year, int day);

private:
	std::filesystem::path inputDir;
	std::shared_ptr<AoCCookie> cookie;

	void downloadInput(int year, int day);
};
