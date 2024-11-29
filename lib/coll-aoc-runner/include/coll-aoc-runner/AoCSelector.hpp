#pragma once

/**
 * @class AoCSelector
 * @brief Selector for Advent of Code puzzles.
 */
struct AoCSelector {
  int year, day, part;

  /**
   * @brief Create a puzzle selector. This selector limits which puzzles are run.
   *
   * @param year Run all puzzles from this year. If -1, run all years.
   * @param day Run the puzzle from this day. If -1, run all days.
   * @param part Run this part of the puzzle. If -1, run all parts.
   */
  AoCSelector(int year = -1, int day = -1, int part = -1)
      : year(year), day(day), part(part) {}
  ~AoCSelector() = default;
};
