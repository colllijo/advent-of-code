cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "COLL-AoC-Runner")
set(LIBRARY_NAME "coll-aoc-runner")
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR "src/")
set(INCLUDE_DIR "include/")

# Set sources
set(SOURCE
  "${SOURCE_DIR}AoCRunner.cpp"
  "${SOURCE_DIR}AoCYear.cpp"
  "${SOURCE_DIR}AoCDay.cpp"
)

# Set headers
set(HEADER
  "${INCLUDE_DIR}${LIBRARY_NAME}/AoCRunner.hpp"
  "${INCLUDE_DIR}${LIBRARY_NAME}/AoCYear.hpp"
  "${INCLUDE_DIR}${LIBRARY_NAME}/AoCDay.hpp"
  "${INCLUDE_DIR}${LIBRARY_NAME}/AoCSelector.hpp"
)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}${SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}${INCLUDE_DIR}"
)

project(${PROJECT_NAME})
add_library(${LIBRARY_NAME} STATIC ${HEADER} ${SOURCE})
target_include_directories(
  ${LIBRARY_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:${INCLUDE_DIR}${LIBRARY_NAME}>
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_DIR}>
)
