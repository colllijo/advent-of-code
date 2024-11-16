#include "2015/Day21.hpp"

#include <climits>
#include <vector>

Day21_2015::Day21_2015() {
	exampleInput = "";
}

struct Setup {
	int cost;
	int damage;
	int armor;
};

struct Gear {
	int cost;
	int damage;
	int armor;
};

const vector<Gear> weapons = {
	{8, 4, 0},
	{10, 5, 0},
	{25, 6, 0},
	{40, 7, 0},
	{74, 8, 0}
};

const vector<Gear> armor = {
	{0, 0, 0},
	{13, 0, 1},
	{31, 0, 2},
	{53, 0, 3},
	{75, 0, 4},
	{102, 0, 5}
};

const vector<Gear> rings = {
	{0, 0, 0},
	{0, 0, 0},
	{25, 1, 0},
	{50, 2, 0},
	{100, 3, 0},
	{20, 0, 1},
	{40, 0, 2},
	{80, 0, 3}
};

string Day21_2015::part1(const string& input, bool example) {
	int minCost = INT_MAX;

	vector<Setup> setups;
	for (const auto& weapon : weapons) {
		for (const auto& armor : armor) {
			for (int i = 0; i < rings.size() - 1; i++) {
				for (int j = i + 1; j < rings.size(); j++) {
					int cost = weapon.cost + armor.cost + rings[i].cost + rings[j].cost;
					int damage = weapon.damage + armor.damage + rings[i].damage + rings[j].damage;
					int defense = armor.armor + rings[i].armor + rings[j].armor;
					setups.push_back({cost, damage, defense});
				}
			}
		}
	}

	for (const auto& setup : setups) {
		int playerDamage = setup.damage;
		int playerDefense = setup.armor;
		int playerHealth = 100;
		int bossDamage = 8;
		int bossDefense = 1;
		int bossHealth = 104;
		while (true) {
			bossHealth -= max(playerDamage - bossDefense, 1);
			if (bossHealth <= 0) {
				minCost = min(minCost, setup.cost);
				break;
			}
			playerHealth -= max(bossDamage - playerDefense, 1);
			if (playerHealth <= 0) {
				break;
			}
		}
	}

	return to_string(minCost);
}

string Day21_2015::part2(const string& input, bool example) {
	int maxCost = 0;

	vector<Setup> setups;
	for (const auto& weapon : weapons) {
		for (const auto& armor : armor) {
			for (int i = 0; i < rings.size() - 1; i++) {
				for (int j = i + 1; j < rings.size(); j++) {
					int cost = weapon.cost + armor.cost + rings[i].cost + rings[j].cost;
					int damage = weapon.damage + armor.damage + rings[i].damage + rings[j].damage; int defense = armor.armor + rings[i].armor + rings[j].armor;
					setups.push_back({cost, damage, defense});
				}
			}
		}
	}

	for (const auto& setup : setups) {
		int playerDamage = setup.damage;
		int playerDefense = setup.armor;
		int playerHealth = 100;
		int bossDamage = 8;
		int bossDefense = 1;
		int bossHealth = 104;
		while (true) {
			bossHealth -= max(playerDamage - bossDefense, 1);
			if (bossHealth <= 0) {
				break;
			}
			playerHealth -= max(bossDamage - playerDefense, 1);
			if (playerHealth <= 0) {
				maxCost = max(maxCost, setup.cost);
				break;
			}
		}
	}

	return to_string(maxCost);
}
