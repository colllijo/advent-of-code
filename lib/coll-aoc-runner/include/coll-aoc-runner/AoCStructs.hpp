#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

enum class AoCSolveState
{
	CORRECT_ANSWER,
	WRONG_ANSWER,
	ANSWER_TOO_HIGH,
	ANSWER_TOO_LOW,
	TOO_MANY_ATTEMPTS,
	ALREADY_SOLVED,
	NOT_SOLVED,
	UNDEFINED
};

inline std::string toString(AoCSolveState state)
{
	switch (state)
	{
		case AoCSolveState::CORRECT_ANSWER: return "CORRECT_ANSWER";
		case AoCSolveState::WRONG_ANSWER: return "WRONG_ANSWER";
		case AoCSolveState::ANSWER_TOO_HIGH: return "ANSWER_TOO_HIGH";
		case AoCSolveState::ANSWER_TOO_LOW: return "ANSWER_TOO_LOW";
		case AoCSolveState::TOO_MANY_ATTEMPTS: return "TOO_MANY_ATTEMPTS";
		case AoCSolveState::ALREADY_SOLVED: return "ALREADY_SOLVED";
		case AoCSolveState::NOT_SOLVED: return "NOT_SOLVED";
		case AoCSolveState::UNDEFINED: return "UNDEFINED";
		default: throw std::invalid_argument("Invalid AoCSolveState");
	}
}

inline AoCSolveState fromString(const std::string &state)
{
	static const std::unordered_map<std::string, AoCSolveState> stateMap = {
		{ "CORRECT_ANSWER", AoCSolveState::CORRECT_ANSWER },
		{ "WRONG_ANSWER", AoCSolveState::WRONG_ANSWER },
		{ "ANSWER_TOO_HIGH", AoCSolveState::ANSWER_TOO_HIGH },
		{ "ANSWER_TOO_LOW", AoCSolveState::ANSWER_TOO_LOW },
		{ "TOO_MANY_ATTEMPTS", AoCSolveState::TOO_MANY_ATTEMPTS },
		{ "ALREADY_SOLVED", AoCSolveState::ALREADY_SOLVED },
		{ "NOT_SOLVED", AoCSolveState::NOT_SOLVED },
		{ "UNDEFINED", AoCSolveState::UNDEFINED }
	};

	auto it = stateMap.find(state);
	if (it != stateMap.end())
	{
		return it->second;
	}

	throw std::invalid_argument("Invalid string for AoCSolveState");
}

inline bool cachable(AoCSolveState state)
{
	switch (state)
	{
		case AoCSolveState::CORRECT_ANSWER:
		case AoCSolveState::WRONG_ANSWER:
		case AoCSolveState::ANSWER_TOO_HIGH:
		case AoCSolveState::ANSWER_TOO_LOW:
		case AoCSolveState::ALREADY_SOLVED:
			return true;
		default:
			return false;
	}
}
