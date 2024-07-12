cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "COLL-AdventOfCode")
set(EXECUTABLE_NAME "coll-aoc")
set(CMAKE_CXX_STANDARD 23)

set(SOURCE_DIR "src/")
set(INCLUDE_DIR "include/")
set(LIBRARY_DIR "lib/")

# Set sources
set(SOURCE "${SOURCE_DIR}main.cpp")

# Set headers
set(HEADER "${INCLUDE_DIR}AoCYears.hpp")

# Set libraries
set(LIBRARIES "coll-aoc-runner")
foreach(library ${LIBRARIES})
  add_subdirectory("${LIBRARY_DIR}${library}")
endforeach()

project(${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCE} ${HEADER}
  ${SOURCE_2015} ${HEADER_2015}
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARIES})

