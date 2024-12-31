cmake_minimum_required (VERSION 3.20.0)
project (clarbe C CXX)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(BUILD_COVERAGE_COMPILE_FLAGS "-Wall")
  set(BUILD_COVERAGE_LINK_FLAGS "")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(BUILD_COVERAGE_COMPILE_FLAGS "-Os -DNDEBUG")
  set(BUILD_COVERAGE_LINK_FLAGS "")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${BUILD_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${BUILD_COVERAGE_LINK_FLAGS}")

include_directories("include")

file(GLOB_RECURSE SRC "include/*.hpp" "include/*.h" "src/*.c" "src/*.cpp")

add_executable(clarbe ${SRC})