#!/bin/bash

set -eou pipefail

usage ()
{
  echo "Usage: $0 <year>"
}

if [[ $# -ne 1 ]] || [[ $1 != +([[:digit:]]) ]]; then
  usage
  exit 1
fi

# Year
YEAR=$1

# Get Script Path
SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")

# Check if year already exists
if [[ -d "$SCRIPT_PATH/../src/$YEAR" ]] || [[ -d "$SCRIPT_PATH/../include/$YEAR" ]]; then
  echo "Year $YEAR already exists."
  exit 0
fi

# Create year directory
mkdir -p "$SCRIPT_PATH/../src/$YEAR"
mkdir -p "$SCRIPT_PATH/../include/$YEAR"

# Copy template files into directories
# AoCYear
FILE="$SCRIPT_PATH/../include/$YEAR/AoCYear$YEAR.hpp"

cp "$SCRIPT_PATH/template/AoCYear.hpp" "$FILE"
sed -i -e "s/\(year_\)/\1$YEAR/i" -e "s/\(Day[0-9]\{2\}_\)/\1$YEAR/g" "$FILE"

for i in {1..25}; do
  printf -v DAY "%02d" "$i"

  # Headers
  FILE="$SCRIPT_PATH/../include/$YEAR/Day$DAY.hpp"

  cp "$SCRIPT_PATH/template/Day.hpp" "$FILE"
  sed -i -e "s/\(AOC_\)/\1$YEAR/" -e "s/\(_DAY_\)/\1$DAY/" -e "s/\(Day\)\(_\)/\1$DAY\2$YEAR/" "$FILE"

  # Sources
  FILE="$SCRIPT_PATH/../src/$YEAR/Day$DAY.cpp"

  cp "$SCRIPT_PATH/template/Day.cpp" "$FILE"
  sed -i -e "s/Day.hpp/$YEAR\/Day$DAY.hpp/" -e "s/\(Day\)\(_\)/\1$DAY\2$YEAR/g" "$FILE"
done

# Add the year to the AoCYears.hpp file
sed -zi -e 's/\(\/\/ Include all AoC Years in one file\n.*\?\n\)\n/\1#include "'"$YEAR"'\/AoCYear'"$YEAR"'.hpp"\n\n/' "$SCRIPT_PATH/../include/AoCYears.hpp"

# Add the year to the runner in the main.cpp file
sed -zi -e 's/\(\/\/ Add years to the runner\n.*\?\n\)\n/\1  runner.addYear('"$YEAR"', AoCYear_'"$YEAR"'());\n\n/' "$SCRIPT_PATH/../src/main.cpp"

# Add the year to the CMakeLists.txt file
sed -zi \
  -e "s/\(add_executable.*\?\n.*\?\n\))/\1  \${SOURCE_$YEAR} \${HEADER_$YEAR}\n)/" \
  -e "s/\(\n\n# Set headers\)/\nset(SOURCE_$YEAR\n  \${SOURCE_DIR}$YEAR\/Day01.cpp\n  \${SOURCE_DIR}$YEAR\/Day02.cpp\n  \${SOURCE_DIR}$YEAR\/Day03.cpp\n  \${SOURCE_DIR}$YEAR\/Day04.cpp\n  \${SOURCE_DIR}$YEAR\/Day05.cpp\n  \${SOURCE_DIR}$YEAR\/Day06.cpp\n  \${SOURCE_DIR}$YEAR\/Day07.cpp\n  \${SOURCE_DIR}$YEAR\/Day08.cpp\n  \${SOURCE_DIR}$YEAR\/Day09.cpp\n  \${SOURCE_DIR}$YEAR\/Day10.cpp\n  \${SOURCE_DIR}$YEAR\/Day11.cpp\n  \${SOURCE_DIR}$YEAR\/Day12.cpp\n  \${SOURCE_DIR}$YEAR\/Day13.cpp\n  \${SOURCE_DIR}$YEAR\/Day14.cpp\n  \${SOURCE_DIR}$YEAR\/Day15.cpp\n  \${SOURCE_DIR}$YEAR\/Day16.cpp\n  \${SOURCE_DIR}$YEAR\/Day17.cpp\n  \${SOURCE_DIR}$YEAR\/Day18.cpp\n  \${SOURCE_DIR}$YEAR\/Day19.cpp\n  \${SOURCE_DIR}$YEAR\/Day20.cpp\n  \${SOURCE_DIR}$YEAR\/Day21.cpp\n  \${SOURCE_DIR}$YEAR\/Day22.cpp\n  \${SOURCE_DIR}$YEAR\/Day23.cpp\n  \${SOURCE_DIR}$YEAR\/Day24.cpp\n  \${SOURCE_DIR}$YEAR\/Day25.cpp\n)\1/g" \
  -e "s/\(\n\n# Set libraries\)/\nset(HEADER_$YEAR\n  \${INCLUDE_DIR}$YEAR\/AoCYear$YEAR.hpp\n  \${INCLUDE_DIR}$YEAR\/Day01.hpp\n  \${INCLUDE_DIR}$YEAR\/Day02.hpp\n  \${INCLUDE_DIR}$YEAR\/Day03.hpp\n  \${INCLUDE_DIR}$YEAR\/Day04.hpp\n  \${INCLUDE_DIR}$YEAR\/Day05.hpp\n  \${INCLUDE_DIR}$YEAR\/Day06.hpp\n  \${INCLUDE_DIR}$YEAR\/Day07.hpp\n  \${INCLUDE_DIR}$YEAR\/Day08.hpp\n  \${INCLUDE_DIR}$YEAR\/Day09.hpp\n  \${INCLUDE_DIR}$YEAR\/Day10.hpp\n  \${INCLUDE_DIR}$YEAR\/Day11.hpp\n  \${INCLUDE_DIR}$YEAR\/Day12.hpp\n  \${INCLUDE_DIR}$YEAR\/Day13.hpp\n  \${INCLUDE_DIR}$YEAR\/Day14.hpp\n  \${INCLUDE_DIR}$YEAR\/Day15.hpp\n  \${INCLUDE_DIR}$YEAR\/Day16.hpp\n  \${INCLUDE_DIR}$YEAR\/Day17.hpp\n  \${INCLUDE_DIR}$YEAR\/Day18.hpp\n  \${INCLUDE_DIR}$YEAR\/Day19.hpp\n  \${INCLUDE_DIR}$YEAR\/Day20.hpp\n  \${INCLUDE_DIR}$YEAR\/Day21.hpp\n  \${INCLUDE_DIR}$YEAR\/Day22.hpp\n  \${INCLUDE_DIR}$YEAR\/Day23.hpp\n  \${INCLUDE_DIR}$YEAR\/Day24.hpp\n  \${INCLUDE_DIR}$YEAR\/Day25.hpp\n)\1/g" \
  "$SCRIPT_PATH/../CMakeLists.txt"

# Prebuild the year to save time when solving the puzzles
bash "$SCRIPT_PATH/build.sh"

echo "Year $YEAR created."

exit 0
