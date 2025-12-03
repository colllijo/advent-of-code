#include "AoCIO.hpp"

#include <termios.h>
#include <unistd.h>

#include <chrono>
#include <print>
#include <string>

#include "AoCStructs.hpp"

bool AoCIO::getConfirmation(const std::string& prompt, bool defaultAnswer)
{
	int retries = 3;

	std::string defaultPrompt = defaultAnswer ? "\033[1;32m[Yes] \033[1;31m[no]\033[0m" : "\033[1;32m[yes] \033[1;31m[No]\033[0m";
	char input;

	while (retries-- >= 0)
	{
		std::print("\033[1;36m─── {} ───\033[0m\n{}\n", prompt, defaultPrompt);
		input = getChar();

		if (input == '\n' || input == '\r')
			return defaultAnswer;
		else if (input == 'y' || input == 'Y')
			return true;
		else if (input == 'n' || input == 'N')
			return false;
		else
			std::print("Please press 'y' or 'n'.\n");
	}

	return false;
}

void AoCIO::printPartResult(int year, int day, int part, const std::string& result, const std::chrono::high_resolution_clock::duration& duration, bool example)
{
	// Top border
	std::print("\033[1;36m╭──────────────────────────────────────────────────────────────────────╮\033[0m\n");

	// Result
	std::print("\033[1;36m│");
	std::print(" \033[1;37mYear\033[0m: \033[1;32m{:4}\033[0m", year);
	std::print("\t\033[1;37mDay\033[0m: \033[1;32m{:2}\033[0m", day);
	std::print("\t\033[1;37mPart\033[0m: \033[1;32m{:2}\033[0m", part);
	std::print("\t\033[1;37mDuration\033[0m: \033[1;32m{}\033[0m", duration);

	if (example) { std::print("\t\033[1;31mExample\033[0m: \033[1;37m{}\033[0m\n", result); }
	else
	{
		std::print("\t\033[1;37m Answer\033[0m: \033[1;32m{}\033[0m\n", result);
	}

	// Bottom border
	std::print("\033[1;36m╰──────────────────────────────────────────────────────────────────────╯\033[0m\n");
}

void AoCIO::printFullPartResult(int year, int day, int part, const std::string& result, const std::string& exampleResult,
    const std::chrono::high_resolution_clock::duration& duration, const std::chrono::high_resolution_clock::duration& exampleDuration)
{
	// Top border
	std::print("\033[1;36m╭──────────────────────────────────────────────────────────────────────╮\033[0m\n");

	// Example
	std::print("\033[1;36m│");
	std::print(" \033[1;37mYear\033[0m: \033[1;32m{:4}\033[0m", year);
	std::print("\t\033[1;37mDay\033[0m: \033[1;32m{:2}\033[0m", day);
	std::print("\t\033[1;37mPart\033[0m: \033[1;32m{:2}\033[0m", part);
	std::print("\t\033[1;37mDuration\033[0m: \033[1;32m{}\033[0m", exampleDuration);
	std::print("\t\033[1;31mExample\033[0m: \033[1;37m{}\033[0m", exampleResult);
	std::print("\n");

	// Actual
	std::print("\033[1;36m│");
	std::print(" \033[1;37mYear\033[0m: \033[1;32m{:4}\033[0m", year);
	std::print("\t\033[1;37mDay\033[0m: \033[1;32m{:2}\033[0m", day);
	std::print("\t\033[1;37mPart\033[0m: \033[1;32m{:2}\033[0m", part);
	std::print("\t\033[1;37mDuration\033[0m: \033[1;32m{}\033[0m", duration);
	std::print("\t\033[1;37m Answer\033[0m: \033[1;32m{}\033[0m", result);
	std::print("\n");

	// Bottom border
	std::print("\033[1;36m╰──────────────────────────────────────────────────────────────────────╯\033[0m\n");
}

void AoCIO::printSolveState(AoCSolveState state, bool cached)
{
	switch (state)
	{
		case AoCSolveState::CORRECT_ANSWER:
		case AoCSolveState::ALREADY_SOLVED:
			std::print("\033[1;36m───── \033[1;32m{}✔ Correct answer! Well done!\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::WRONG_ANSWER:
			std::print("\033[1;36m───── \033[1;31m{}✖ Incorrect answer! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::ANSWER_TOO_HIGH:
			std::print("\033[1;36m───── \033[1;33m{}⚠ Your answer is too high! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::ANSWER_TOO_LOW:
			std::print("\033[1;36m───── \033[1;33m{}⚠ Your answer is too low! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::TOO_MANY_ATTEMPTS:
			std::print("\033[1;36m───── \033[1;35m❌ Too many attempts! Try again later.\033[0m\n\n");
			break;
		default:
			break;
	}
}

void AoCIO::printError(const std::string& error) { std::print("\033[1;31m{}\033[0m\n", error); }

char AoCIO::getChar()
{
	char buf = 0;
	struct termios old = {0};

	if (tcgetattr(0, &old) < 0) perror("tcsetattr()");

	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;

	if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0) perror("read()");

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;

	if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");

	return buf;
}
