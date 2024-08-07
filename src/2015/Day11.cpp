#include "2015/Day11.hpp"

Day11_2015::Day11_2015() {
  exampleInput = "abcdefgh";
}

bool validPassword(const string &password) {
  bool rule1 = false;

  int pairs = 0;
  bool skip = false;

  for (int i = 0; i + 1 < password.size(); i++) {
    if (rule1 && pairs >= 2) return true;
    if (rule1 == false && i + 2 < password.size()) {
      if (password.at(i) + 1 == password.at(i + 1) && password.at(i) + 2 == password.at(i + 2))
        rule1 = true;
    }

    if (skip) { skip = false; continue; }
    if (password.at(i) == password.at(i + 1)) {
      pairs++;

      if (rule1 == true) i++;
      else skip = true;
    }
  }

  return rule1 && pairs >= 2;
}

string incrementPassword(const string& password) {
  string incrementedPassword = password;

  do {
    for (int i = incrementedPassword.size() - 1; i >= 0; i--) {
      if (incrementedPassword[i] == 'z') {
        incrementedPassword[i] = 'a';
      } else {
        incrementedPassword[i]++;

        // Rule 2
        if (incrementedPassword[i] == 'i' || incrementedPassword[i] == 'o' || incrementedPassword[i] == 'l')
          incrementedPassword[i]++;

        break;
      }
    }
  } while (!validPassword(incrementedPassword));

  return incrementedPassword;
}

string Day11_2015::part1(const string& input, bool example) {
  return incrementPassword(input);
}

string Day11_2015::part2(const string& input, bool example) {
  return incrementPassword(incrementPassword(input));
}
