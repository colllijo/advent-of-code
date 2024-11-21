#include "2016/Day06.hpp"

#include <sstream>
#include <unordered_map>
#include <vector>

Day06_2016::Day06_2016() {
	exampleInput = "eedadn\n"
                 "drvtee\n"
                 "eandsr\n"
                 "raavrd\n"
                 "atevrs\n"
                 "tsrnev\n"
                 "sdttsa\n"
                 "rasrtv\n"
                 "nssdts\n"
                 "ntnada\n"
                 "svetve\n"
                 "tesnvt\n"
                 "vntsnd\n"
                 "vrdear\n"
                 "dvrsen\n"
                 "enarar\n";
}

string Day06_2016::part1(const string& input, bool example) { 
  int len = input.find('\n');

  vector<string> vals(len, string());
  auto mostCommon = [](const string& vals)
  {
    unordered_map<char, int> fqz;

    for (const auto c : vals)
    {
      fqz[c]++;
    }

    char mostCommon = vals[0];
    for (const auto& [val, fq] : fqz)
    {
      if (fq > fqz[mostCommon])
      {
        mostCommon = val;
      }
    }

    return mostCommon;
  };

  stringstream stream(input); string line;
  while (getline(stream, line))
  {
    for (int i = 0; i < len; i++)
    {
      vals[i].push_back(line[i]);
    }
  }

  string result = "";
  for (int i = 0; i < len; i++)
  {
    result += mostCommon(vals[i]);
  }
  
  return result;
}

string Day06_2016::part2(const string& input, bool example) {
    int len = input.find('\n');

  vector<string> vals(len, string());
  auto lestCommon = [](const string& vals)
  {
    unordered_map<char, int> fqz;

    for (const auto c : vals)
    {
      fqz[c]++;
    }

    char mostCommon = vals[0];
    for (const auto& [val, fq] : fqz)
    {
      if (fq < fqz[mostCommon])
      {
        mostCommon = val;
      }
    }

    return mostCommon;
  };

  stringstream stream(input); string line;
  while (getline(stream, line))
  {
    for (int i = 0; i < len; i++)
    {
      vals[i].push_back(line[i]);
    }
  }

  string result = "";
  for (int i = 0; i < len; i++)
  {
    result += lestCommon(vals[i]);
  }
  
  return result;
}
