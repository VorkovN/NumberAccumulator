cmake_minimum_required(VERSION 3.22)
project(NumberAccumulator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS -pthread)

message("Apps building:")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    find_package (GTest)
endif()

add_subdirectory(Src)
