#include "AoCSubmitter.hpp"

#include <curl/curl.h>

#include <memory>
#include <tuple>

#include "AoCException.hpp"
#include "AoCStructs.hpp"

AoCSubmitter::AoCSubmitter(const std::shared_ptr<AoCCache> &aocCache, const std::shared_ptr<AoCCookie> &aocCookie) : cache(aocCache), cookie(aocCookie), aocIO(AoCIO::getInstance())
{
}
AoCSubmitter::~AoCSubmitter() = default;

std::tuple<AoCSolveState, bool> AoCSubmitter::submit(int year, int day, int part, const std::string &answer)
{
	auto cached = cache->get(std::to_string(year) + "/" + std::to_string(day) + "/" + std::to_string(part) + "/" + answer);
	if (cached.has_value())
	{
		return {fromString(cached.value()), true};
	}

	if (!aocIO.getConfirmation("Submit answer to AoC", false))
	{
		return {AoCSolveState::UNDEFINED, false};
	}

	AoCSolveState response = submitAnswer(year, day, part, answer);

	if (cachable(response))
	{
		AoCSolveState state = response;
		if (state == AoCSolveState::CORRECT_ANSWER)
		{
			state = AoCSolveState::ALREADY_SOLVED;
		}

		cache->set(std::to_string(year) + "/" + std::to_string(day) + "/" + std::to_string(part) + "/" + answer, toString(state));
	}

	return {response, false};
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

AoCSolveState AoCSubmitter::submitAnswer(int year, int day, int part, const std::string &answer)
{
	std::string url = "https://adventofcode.com/" + std::to_string(year) + "/day/" + std::to_string(day) + "/answer";
	std::string data = "level=" + std::to_string(part) + "&answer=" + answer;
	std::string readBuffer;

	CURL *curl = curl_easy_init();
	if (!curl)
    throw AoCException("Could not initialize curl");
	
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_COOKIE, ("session=" + cookie->getSession()).c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		curl_easy_cleanup(curl);
    throw AoCException("Failed to submit answer");
	}

	// Cleanup
	curl_easy_cleanup(curl);

	readBuffer = readBuffer.substr(readBuffer.find("<main>\n") + 7, readBuffer.find("</main>") - readBuffer.find("<main>\n") - 7);
	if (readBuffer.find("Both parts of this puzzle are complete! They provide two gold stars: **") != std::string::npos ||
	    (readBuffer.find("The first half of this puzzle is complete! It provides one gold star: *") != std::string::npos && part == 1) ||
	    readBuffer.find("You don't seem to be solving the right level.  Did you already complete it?") != std::string::npos)
	{
		return AoCSolveState::ALREADY_SOLVED;
	}
	else if (readBuffer.find("That's the right answer!") != std::string::npos)
	{
		return AoCSolveState::CORRECT_ANSWER;
	}
	else if (readBuffer.find("answer is too high") != std::string::npos)
	{
		return AoCSolveState::ANSWER_TOO_HIGH;
	}
	else if (readBuffer.find("answer is too low") != std::string::npos)
	{
		return AoCSolveState::ANSWER_TOO_LOW;
	}
	else if (readBuffer.find("That's not the right answer") != std::string::npos)
	{
		return AoCSolveState::WRONG_ANSWER;
	}
	else if (readBuffer.find("You gave an answer too recently") != std::string::npos)
	{
		return AoCSolveState::TOO_MANY_ATTEMPTS;
	}
	else
	{
		printf("Received unknown response:\n %s\n\n", readBuffer.c_str());
		return AoCSolveState::UNDEFINED;
	}
}
