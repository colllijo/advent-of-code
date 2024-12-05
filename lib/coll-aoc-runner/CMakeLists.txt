cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "COLL-AoC-Runner")
set(LIBRARY_NAME "coll-aoc-runner")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")

# Set sources
set(SOURCE
  "${SOURCE_DIR}/AoCRunner.cpp"
  "${SOURCE_DIR}/AoCYear.cpp"
  "${SOURCE_DIR}/AoCInput.cpp"
  "${SOURCE_DIR}/AoCDay.cpp"
  "${SOURCE_DIR}/AoCSubmitter.cpp"
  "${SOURCE_DIR}/AoCIO.cpp"
  "${SOURCE_DIR}/AoCCookie.cpp"
  "${SOURCE_DIR}/strings/Format.cpp"
  "${SOURCE_DIR}/cache/AoCCache.cpp"
  "${SOURCE_DIR}/cache/AoCLocalCache.cpp"
)

# Set headers
set(HEADER
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCRunner.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCYear.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCDay.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCInput.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCSelector.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCSubmitter.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCStructs.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCIO.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/AoCCookie.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/strings/Format.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/structs/Grid.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/crypto/MD5.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/cache/AoCCache.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/cache/AoCLocalCache.hpp"
  "${INCLUDE_DIR}/${LIBRARY_NAME}/math/Math.hpp"
)

include_directories(
  "${CMAKE_CURRENT_SOURCE_DIR}${SOURCE_DIR}"
  "${CMAKE_CURRENT_SOURCE_DIR}${INCLUDE_DIR}"
)

# Add libraries
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

## Optional sqlite3 for reading session cookie from browser
find_package(SQLite3 QUIET)

if(SQLite3_FOUND)
  add_compile_definitions(SQLITE3_FOUND)
endif()

project(${PROJECT_NAME})
add_library(${LIBRARY_NAME} STATIC ${HEADER} ${SOURCE})
target_include_directories(
  ${LIBRARY_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}/${LIBRARY_NAME}>
    $<INSTALL_INTERFACE:${INCLUDE_DIR}/${LIBRARY_NAME}>
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:${INCLUDE_DIR}>
)
target_link_libraries(${LIBRARY_NAME} PRIVATE
  CURL::libcurl
  OpenSSL::SSL
  OpenSSL::Crypto
)

if(SQLite3_FOUND)
  target_link_libraries(${LIBRARY_NAME} PRIVATE ${SQLite3_LIBRARIES})
endif()
