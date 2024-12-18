#include "AoCIO.hpp"

#include <string>
#include <termios.h>
#include <unistd.h>

#include "AoCStructs.hpp"

bool AoCIO::getConfirmation(const std::string& prompt, bool defaultAnswer)
{
	int retries = 3;

	std::string defaultPrompt = defaultAnswer ? "\033[1;32m[Yes] \033[1;31m[no]\033[0m" : "\033[1;32m[yes] \033[1;31m[No]\033[0m";
	char input;

	while (retries-- >= 0)
	{
		printf("\033[1;36m─── %s ───\033[0m\n%s\n", prompt.c_str(), defaultPrompt.c_str());
        input = getChar();

        if (input == '\n' || input == '\r') return defaultAnswer;
        else if (input == 'y' || input == 'Y') return true;
        else if (input == 'n' || input == 'N') return false;
        else printf("Please press 'y' or 'n'.\n");
	}

	return false;
}

void AoCIO::printPartResult(int year, int day, int part, const std::string& result, bool example)
{
	// Top border
	printf("\033[1;36m╭──────────────────────────────────────────────╮\033[0m\n");

	// Result
	printf("\033[1;36m│");
	printf(" \033[1;37mYear\033[0m: \033[1;32m%4d\033[0m", year);
	printf("\t\033[1;37mDay\033[0m: \033[1;32m%2d\033[0m", day);
	printf("\t\033[1;37mPart\033[0m: \033[1;32m%2d\033[0m", part);

	if (example) printf("\t\033[1;31mExample\033[0m: \033[1;37m%s\033[0m\n", result.c_str());
	else printf("\t\033[1;37m Answer\033[0m: \033[1;32m%s\033[0m\n", result.c_str());

	// Bottom border
	printf("\033[1;36m╰──────────────────────────────────────────────╯\033[0m\n");
}

void AoCIO::printFullPartResult(int year, int day, int part, const std::string& result, const std::string& exampleResult)
{
	// Top border
	printf("\033[1;36m╭──────────────────────────────────────────────╮\033[0m\n");

	// Example
	printf("\033[1;36m│");
	printf(" \033[1;37mYear\033[0m: \033[1;32m%4d\033[0m", year);
	printf("\t\033[1;37mDay\033[0m: \033[1;32m%2d\033[0m", day);
	printf("\t\033[1;37mPart\033[0m: \033[1;32m%2d\033[0m", part);
	printf("\t\033[1;31mExample\033[0m: \033[1;37m%s\033[0m", exampleResult.c_str());
	printf("\n");

	// Actual
	printf("\033[1;36m│");
	printf(" \033[1;37mYear\033[0m: \033[1;32m%4d\033[0m", year);
	printf("\t\033[1;37mDay\033[0m: \033[1;32m%2d\033[0m", day);
	printf("\t\033[1;37mPart\033[0m: \033[1;32m%2d\033[0m", part);
	printf("\t\033[1;37m Answer\033[0m: \033[1;32m%s\033[0m", result.c_str());
	printf("\n");

	// Bottom border
	printf("\033[1;36m╰──────────────────────────────────────────────╯\033[0m\n");
}

void AoCIO::printSolveState(AoCSolveState state, bool cached)
{
	switch (state)
	{
		case AoCSolveState::CORRECT_ANSWER:
		case AoCSolveState::ALREADY_SOLVED:
			printf("\033[1;36m───── \033[1;32m%s✔ Correct answer! Well done!\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::WRONG_ANSWER:
			printf("\033[1;36m───── \033[1;31m%s✖ Incorrect answer! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::ANSWER_TOO_HIGH:
			printf("\033[1;36m───── \033[1;33m%s⚠ Your answer is too high! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::ANSWER_TOO_LOW:
			printf("\033[1;36m───── \033[1;33m%s⚠ Your answer is too low! Try again.\033[0m\n\n", cached ? "≡ " : "");
			break;
		case AoCSolveState::TOO_MANY_ATTEMPTS:
			printf("\033[1;36m───── \033[1;35m❌ Too many attempts! Try again later.\033[0m\n\n");
			break;
		default:
			break;
	}
}

void AoCIO::printError(const std::string& error)
{
  printf("\033[1;31m%s\033[0m\n", error.c_str());
}

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
