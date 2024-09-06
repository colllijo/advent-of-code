#include "2015/Day15.hpp"
#include <cstring>
#include <cwchar>
#include <sstream>
#include <vector>

Day15_2015::Day15_2015() {
  exampleInput = "";
}

struct Ingredient {
  string name;

  int capacity;
  int durability;
  int flavor;
  int texture;
  int calories;
};

string Day15_2015::part1(const string& input, bool example) {
  int bestCookieScore = 0;
  vector<Ingredient> ingredients;

  stringstream stream(input); string line;
  while (getline(stream, line)) {
    Ingredient ingredient;

    char name[32];
    sscanf(line.c_str(), "%31s capacity %d, durability %d, flavor %d, texture %d, calories %d",
         name, &ingredient.capacity, &ingredient.durability, &ingredient.flavor, &ingredient.texture, &ingredient.calories);
    ingredient.name = name;

    ingredients.push_back(ingredient);
  }

  for (int first = 0; first <= 100; first++) {
    for (int second = 0; second <= 100 - first; second++) {
      for (int third = 0; third <= 100 - first - second; third++) {
        int fourth = max(0, 100 - first - second - third);

        bestCookieScore = max(
          bestCookieScore,
          (
            max(0, ingredients[0].capacity * first + ingredients[1].capacity * second + ingredients[2].capacity * third + ingredients[3].capacity * fourth) *
            max(0, ingredients[0].durability * first + ingredients[1].durability * second + ingredients[2].durability * third + ingredients[3].durability * fourth) *
            max(0, ingredients[0].flavor * first + ingredients[1].flavor * second + ingredients[2].flavor * third + ingredients[3].flavor * fourth) *
            max(0, ingredients[0].texture * first + ingredients[1].texture * second + ingredients[2].texture * third + ingredients[3].texture * fourth)
          )
        );
      }
    }
  }

  return to_string(bestCookieScore);
}

string Day15_2015::part2(const string& input, bool example) {
  int bestCookieScore = 0;
  vector<Ingredient> ingredients;

  stringstream stream(input); string line;
  while (getline(stream, line)) {
    Ingredient ingredient;

    char name[32];
    sscanf(line.c_str(), "%31s capacity %d, durability %d, flavor %d, texture %d, calories %d",
         name, &ingredient.capacity, &ingredient.durability, &ingredient.flavor, &ingredient.texture, &ingredient.calories);
    ingredient.name = name;

    ingredients.push_back(ingredient);
  }

  for (int first = 0; first <= 100; first++) {
    for (int second = 0; second <= 100 - first; second++) {
      for (int third = 0; third <= 100 - first - second; third++) {
        int fourth = max(0, 100 - first - second - third);

        if (ingredients[0].calories * first + ingredients[1].calories * second + ingredients[2].calories * third + ingredients[3].calories * fourth != 500) continue;

        bestCookieScore = max(
          bestCookieScore,
          (
            max(0, ingredients[0].capacity * first + ingredients[1].capacity * second + ingredients[2].capacity * third + ingredients[3].capacity * fourth) *
            max(0, ingredients[0].durability * first + ingredients[1].durability * second + ingredients[2].durability * third + ingredients[3].durability * fourth) *
            max(0, ingredients[0].flavor * first + ingredients[1].flavor * second + ingredients[2].flavor * third + ingredients[3].flavor * fourth) *
            max(0, ingredients[0].texture * first + ingredients[1].texture * second + ingredients[2].texture * third + ingredients[3].texture * fourth)
          )
        );
      }
    }
  }

  return to_string(bestCookieScore);
}
