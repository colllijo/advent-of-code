#include "AoCInput.hpp"

#include <curl/curl.h>

#include <cstdlib>
#include <cwchar>
#include <fstream>

AoCInput::AoCInput(const std::shared_ptr<AoCCookie>& aocCookie): cookie(aocCookie)
{
	// Check if a root directory is set else use `<PROJECT_ROOT>/input/`
	char *root = getenv("CAOC_ROOT_DIR");
	if (root == nullptr)
	{
		// Assume the binary is in the build folder
		std::filesystem::path exe = std::filesystem::canonical("/proc/self/exe");
		inputDir = exe.parent_path().parent_path() / "input";
	}
	else
	{
		inputDir = std::string(root) + "/input";
	}

	// Make sure the input directroy exists
	if (!std::filesystem::exists(inputDir)) std::filesystem::create_directory(inputDir);
}

AoCInput::~AoCInput() = default;

std::string AoCInput::getInput(int year, int day)
{
	std::ifstream inputFile(inputDir / std::to_string(year) / ("day" + std::to_string(day) + ".txt"));
	std::string input;

	if (!inputFile)
	{
		downloadInput(year, day);
		inputFile.open(inputDir / std::to_string(year) / ("day" + std::to_string(day) + ".txt"));
	}

	if (inputFile && inputFile.is_open())
	{
		input = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		if (input.ends_with('\n')) input.pop_back();
	}
	else
	{
		fprintf(stderr,
		        "\033[31mError loading the input: Input file not found "
		        "please try to manually create it.\033[0m\n");
		exit(1);
	}

	return input;
}

void AoCInput::downloadInput(int year, int day)
{
	// Make sure the directory for the year exists
	if (!std::filesystem::is_directory(inputDir / std::to_string(year))) std::filesystem::create_directory(inputDir / std::to_string(year));

	std::string url = "https://adventofcode.com/" + std::to_string(year) + "/day/" + std::to_string(day) + "/input";
	std::string filename = inputDir.string() + "/" + std::to_string(year) + "/day" + std::to_string(day) + ".txt";

	CURL *curl = curl_easy_init();
	FILE *fp = fopen(filename.c_str(), "wb");
	if (!curl)
	{
		fprintf(stderr, "Could not initialize curl\n");
		exit(1);
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_COOKIE, ("session=" + cookie->getSession()).c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, nullptr);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		fprintf(stderr, "\033[31mFailed to download: %s\033[0m\n", curl_easy_strerror(res));
		fclose(fp);
		curl_easy_cleanup(curl);
		exit(1);
	}

	// Cleanup
	fclose(fp);
	curl_easy_cleanup(curl);
}
