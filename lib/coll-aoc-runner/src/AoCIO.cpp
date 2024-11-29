#include "AoCIO.hpp"

#include <algorithm>
#include <iostream>

bool AoCIO::getConfirmation(const std::string& prompt, bool defaultAnswer)
{
	std::string defaultPrompt = defaultAnswer ? "[Y/n]" : "[y/N]";
	std::string input;

	for (;;)
	{
		printf("%s %s: ", prompt.c_str(), defaultPrompt.c_str());
		std::getline(std::cin, input);

		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		if (input.empty())
		{
			return defaultAnswer;
		}
		else if (input == "y" || input == "yes")
		{
			return true;
		}
		else if (input == "n" || input == "no")
		{
			return false;
		}
		else
		{
			printf("Please enter 'y' or 'n'.\n");
		}
	}
}
