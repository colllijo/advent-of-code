#include "2015/Day22.hpp"

#include <optional>
#include <queue>
#include <vector>

Day22_2015::Day22_2015() { exampleInput = "Something so that the example is run"; }

enum class Effect
{
	SHIELD,
	POISON,
	RECHARGE,
	NONE
};

struct Spell
{
	int cost;
	int damage;
	int heal;
	Effect effect;
	int duration;
};

struct GameState
{
	int playerHealth;
	int playerMana;

	int bossHealth;

	vector<pair<Effect, int>> playerEffects;

	int manaSpent;
};

struct CompareManaSpent {
    bool operator()(const GameState& a, const GameState& b) {
        return a.manaSpent > b.manaSpent; // Min-heap based on manaSpent
    }
};

const vector<Spell> spells{
    {53, 4, 0, Effect::NONE, 0},      // Magic Missile
    {73, 2, 2, Effect::NONE, 0},      // Drain
    {113, 0, 0, Effect::SHIELD, 6},   // Shield
    {173, 0, 0, Effect::POISON, 6},   // Poison
    {229, 0, 0, Effect::RECHARGE, 5}  // Recharge
};

optional<GameState> playTurn(const GameState& state, const Spell& spell, bool example, bool hardMode = false)
{
	GameState newState = state;
  vector<pair<Effect, int>> effects;

  // Hardmode
  if (hardMode)
  {
    newState.playerHealth -= 1;
    if (newState.playerHealth <= 0)
    {
      return nullopt;
    }
  }

	// Player turn
	// Apply effects
  effects = newState.playerEffects;
  newState.playerEffects.clear();
	for (const auto& [effect, duration] : effects)
	{
		switch (effect)
		{
			case Effect::POISON:
				newState.bossHealth -= 3;
				break;
			case Effect::RECHARGE:
				newState.playerMana += 101;
				break;
      case Effect::SHIELD:
			case Effect::NONE:
			default:
				break;
		}

		if (duration > 1)
		{
			newState.playerEffects.push_back({effect, duration - 1});
		}
	}

	// Cast player spell
	if (spell.cost > newState.playerMana)
	{
		return nullopt;
	}

  newState.playerMana -= spell.cost;
  newState.manaSpent += spell.cost;
  newState.playerHealth += spell.heal;
  newState.bossHealth -= spell.damage;

  if (spell.effect != Effect::NONE)
  {
    newState.playerEffects.push_back({spell.effect, spell.duration});
  }

  // Early player win
  if (newState.bossHealth <= 0)
  {
    return newState;
  }

	// Boss turn
	int playerArmor = 0;

  // Apply effects
  effects = newState.playerEffects;
  newState.playerEffects.clear();
	for (const auto& [effect, duration] : effects)
	{
		switch (effect)
		{
      case Effect::SHIELD:
        playerArmor = 7;
        break;
			case Effect::POISON:
				newState.bossHealth -= 3;
				break;
			case Effect::RECHARGE:
				newState.playerMana += 101;
				break;
			case Effect::NONE:
			default:
				break;
		}

		if (duration > 1)
		{
			newState.playerEffects.push_back({effect, duration - 1});
		}
	}

  // Player win
  if (newState.bossHealth <= 0)
  {
    return newState;
  }

  // Boss attack
  newState.playerHealth -= max(1, (example ? 8 : 10) - playerArmor);

  // Player loss
  if (newState.playerHealth <= 0)
  {
    return nullopt;
  }

	return newState;
}

vector<Spell> validSpells(const GameState& state)
{
  vector<Spell> validSpells;
  for (const auto& spell : spells)
  {
    bool valid = true;
    for (const auto& [effect, duration] : state.playerEffects)
    {
      if (effect == spell.effect && duration > 1)
      {
        valid = false;
        break;
      }
    }
    if (valid)
    {
      validSpells.push_back(spell);
    }
  }
  return validSpells;
}

// Boss health: 71, damage: 10
string Day22_2015::part1(const string& input, bool example)
{
  GameState genisis;
  if (example) {
    genisis = {10, 250, 13, {}, 0};
  } else {
    genisis = {50, 500, 71, {}, 0};
  }

  priority_queue<GameState, vector<GameState>, CompareManaSpent> states;
  states.push(genisis);

  while (!states.empty())
  {
    GameState state = states.top();
    states.pop();

    // Player win
    if (state.bossHealth <= 0)
    {
      return to_string(state.manaSpent);
    }

    auto castable = validSpells(state);
    for (const auto& spell : castable)
    {
      auto newState = playTurn(state, spell, example);
      if (newState.has_value())
      {
        states.push(newState.value());
      }
    }
  }

	return "No solution found.";
}

string Day22_2015::part2(const string& input, bool example)
{
  GameState genisis;
  if (example) {
    genisis = {10, 250, 13, {}, 0};
  } else {
    genisis = {50, 500, 71, {}, 0};
  }

  priority_queue<GameState, vector<GameState>, CompareManaSpent> states;
  states.push(genisis);

  while (!states.empty())
  {
    GameState state = states.top();
    states.pop();

    // Player win
    if (state.bossHealth <= 0)
    {
      return to_string(state.manaSpent);
    }

    auto castable = validSpells(state);
    for (const auto& spell : castable)
    {
      auto newState = playTurn(state, spell, example, true);
      if (newState.has_value())
      {
        states.push(newState.value());
      }
    }
  }

	return "No solution found.";
}
