#include "AoCInput.hpp"
#include "curlpp/Easy.hpp"
#include "curlpp/Exception.hpp"
#include "curlpp/Options.hpp"
#include "curlpp/cURLpp.hpp"

#include <cstdlib>
#include <cwchar>
#include <filesystem>
#include <fstream>

AoCInput::AoCInput() {
  // Check if an input directory is set else use `<PROJECT_ROOT>/input/`
  char *input = getenv("CAOC_INPUT_DIR");
  if (input == nullptr) {
    // Assume the binary is in the build folder
    std::filesystem::path exe = std::filesystem::canonical("/proc/self/exe");
    inputDir = exe.parent_path().parent_path() / "input";
  } else {
    inputDir = input;
  }

  // Make sure the input directroy exists
  if (!std::filesystem::exists(inputDir))
    std::filesystem::create_directory(inputDir);
}

AoCInput::~AoCInput() = default;

std::string AoCInput::getInput(int year, int day) {
  std::ifstream inputFile (inputDir / std::to_string(year) / ("day" + std::to_string(day) + ".txt"));
  std::string input;

  if (!inputFile) {
    downloadInput(year, day);
    inputFile.open(inputDir / std::to_string(year) / ("day" + std::to_string(day) + ".txt"));
  }

  if (inputFile && inputFile.is_open()) {
    input = std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    if (input.ends_with('\n')) input.pop_back();
  } else {
    fwprintf(stderr, L"\033[31mError loading the input: Input file not found please try to manually create it.\033[0m\n");
    exit(1);
  }

  return input;
}

void AoCInput::loadAuthCookie() {
  char *cookie = getenv("CAOC_AUTH");
  if (cookie == nullptr) {
    fwprintf(stderr, L"\033[31mAuthorisation cookie not set.\nPlease set the `CAOC_AUTH` environment variable.\033[0m\n");
    exit(1);
  }

  authCookie = cookie;
}

void AoCInput::downloadInput(int year, int day) {
  loadAuthCookie();

  // Make sure the directory for the year exists
	if (!std::filesystem::is_directory(inputDir / std::to_string(year)))
    std::filesystem::create_directory(inputDir / std::to_string(year));

  std::string url = "https://adventofcode.com/" + std::to_string(year) + "/day/" + std::to_string(day) + "/input";
  std::string filename = inputDir.string() + "/" + std::to_string(year) + "/day" + std::to_string(day) + ".txt";

  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    std::ofstream file(filename.c_str(), std::ios::binary | std::ios::out);
    if (!file) {
      fwprintf(stderr, L"Could not open file to write input\n");
      exit(1);
    }

    request.setOpt(new curlpp::options::WriteStream(&file));
    request.setOpt(new curlpp::options::Url(url));
    request.setOpt(new curlpp::options::Cookie("session=" + authCookie));
    request.perform();

    file.close();

    return;
  } catch (curlpp::LogicError & exception) {
    fwprintf(stderr, L"%s\n", exception.what());
  } catch (curlpp::RuntimeError & exception) {
    fwprintf(stderr, L"%s\n", exception.what());
  }

  exit(1);
}
