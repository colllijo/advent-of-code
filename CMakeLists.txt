cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "COLL-AdventOfCode")
set(EXECUTABLE_NAME "coll-aoc")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "src/")
set(INCLUDE_DIR "include/")
set(LIBRARY_DIR "lib/")

# Set sources
set(SOURCE "${SOURCE_DIR}main.cpp")
set(SOURCE_2015
  ${SOURCE_DIR}2015/Day01.cpp
  ${SOURCE_DIR}2015/Day02.cpp
  ${SOURCE_DIR}2015/Day03.cpp
  ${SOURCE_DIR}2015/Day04.cpp
  ${SOURCE_DIR}2015/Day05.cpp
  ${SOURCE_DIR}2015/Day06.cpp
  ${SOURCE_DIR}2015/Day07.cpp
  ${SOURCE_DIR}2015/Day08.cpp
  ${SOURCE_DIR}2015/Day09.cpp
  ${SOURCE_DIR}2015/Day10.cpp
  ${SOURCE_DIR}2015/Day11.cpp
  ${SOURCE_DIR}2015/Day12.cpp
  ${SOURCE_DIR}2015/Day13.cpp
  ${SOURCE_DIR}2015/Day14.cpp
  ${SOURCE_DIR}2015/Day15.cpp
  ${SOURCE_DIR}2015/Day16.cpp
  ${SOURCE_DIR}2015/Day17.cpp
  ${SOURCE_DIR}2015/Day18.cpp
  ${SOURCE_DIR}2015/Day19.cpp
  ${SOURCE_DIR}2015/Day20.cpp
  ${SOURCE_DIR}2015/Day21.cpp
  ${SOURCE_DIR}2015/Day22.cpp
  ${SOURCE_DIR}2015/Day23.cpp
  ${SOURCE_DIR}2015/Day24.cpp
  ${SOURCE_DIR}2015/Day25.cpp
)

# Set headers
set(HEADER "${INCLUDE_DIR}AoCYears.hpp")
set(HEADER_2015
  ${INCLUDE_DIR}2015/AoCYear2015.hpp
  ${INCLUDE_DIR}2015/Day01.hpp
  ${INCLUDE_DIR}2015/Day02.hpp
  ${INCLUDE_DIR}2015/Day03.hpp
  ${INCLUDE_DIR}2015/Day04.hpp
  ${INCLUDE_DIR}2015/Day05.hpp
  ${INCLUDE_DIR}2015/Day06.hpp
  ${INCLUDE_DIR}2015/Day07.hpp
  ${INCLUDE_DIR}2015/Day08.hpp
  ${INCLUDE_DIR}2015/Day09.hpp
  ${INCLUDE_DIR}2015/Day10.hpp
  ${INCLUDE_DIR}2015/Day11.hpp
  ${INCLUDE_DIR}2015/Day12.hpp
  ${INCLUDE_DIR}2015/Day13.hpp
  ${INCLUDE_DIR}2015/Day14.hpp
  ${INCLUDE_DIR}2015/Day15.hpp
  ${INCLUDE_DIR}2015/Day16.hpp
  ${INCLUDE_DIR}2015/Day17.hpp
  ${INCLUDE_DIR}2015/Day18.hpp
  ${INCLUDE_DIR}2015/Day19.hpp
  ${INCLUDE_DIR}2015/Day20.hpp
  ${INCLUDE_DIR}2015/Day21.hpp
  ${INCLUDE_DIR}2015/Day22.hpp
  ${INCLUDE_DIR}2015/Day23.hpp
  ${INCLUDE_DIR}2015/Day24.hpp
  ${INCLUDE_DIR}2015/Day25.hpp
)

# Set libraries
add_subdirectory("${LIBRARY_DIR}coll-aoc-runner")

# Add libraries
find_package(nlohmann_json REQUIRED)

project(${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCE} ${HEADER}
  ${SOURCE_2015} ${HEADER_2015}
  ${SOURCE_2015} ${HEADER_2015}
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
  coll-aoc-runner
  nlohmann_json::nlohmann_json
)
