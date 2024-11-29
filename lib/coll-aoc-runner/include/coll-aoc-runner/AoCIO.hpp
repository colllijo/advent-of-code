#pragma once

#include <string>
class AoCIO
{
public:
	static AoCIO& getInstance()
	{
		static AoCIO instance;
		return instance;
	}

	bool getConfirmation(const std::string& prompt, bool defaultAnswer = false);

private:
	AoCIO() = default;
	AoCIO(const AoCIO&) = delete;
	AoCIO& operator=(const AoCIO&) = delete;
};
