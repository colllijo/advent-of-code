#include "2015/Day12.hpp"
#include "nlohmann/json_fwd.hpp"

#include <cwchar>
#include <nlohmann/json.hpp>

Day12_2015::Day12_2015() {
  // exampleInput = "{\"a\":2,\"b\":4}";
  exampleInput = "[1,{\"c\":\"red\",\"b\":2},3]";
}

string Day12_2015::part1(const string& input, bool example) {
  int sum = 0;

  string currentNumber = "";

  for (const auto& c : input) {
    if (isdigit(c) || (c == '-' && currentNumber.empty())) {
      currentNumber += c;
    } else {
      if (!currentNumber.empty()) {
      sum += stoi(currentNumber);
      currentNumber = "";
      }
    }
  }

  return to_string(sum);
}

int countJson(nlohmann::basic_json<> json) {
  if (json.is_number_integer()) {
    return json.get<int>();
  }

  int value = 0;

  if (json.is_object()) {
    bool hasRed = false;
    for (const auto& [key, element] : json.items()) {
      if (key == "red" || element.is_string() && element.get<string>() == "red") {
        return 0;
      }
    }

    for (const auto& [key, element] : json.items()) {
      value += countJson(element);
    }
  } else if (json.is_array()) {
    for (const auto& element : json) {
      value += countJson(element);
    }
  }

  return value;
}

string Day12_2015::part2(const string& input, bool example) {
  nlohmann::json json = nlohmann::json::parse(input);
  return to_string(countJson(json));
}
