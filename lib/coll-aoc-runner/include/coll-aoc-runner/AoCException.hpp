#pragma once

#include <string>

class AoCException : public std::exception
{
public:
	explicit AoCException(const std::string &message) : message(message) {}

	const char *what() const noexcept override { return message.c_str(); }

private:
	std::string message;
};
