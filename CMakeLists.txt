cmake_minimum_required(VERSION 3.16.3)
project(NumberAccumulator)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS -pthread)

message("Apps building:")
add_subdirectory(Src)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Test building:")
    find_package (GTest)
    add_subdirectory(Tests)
endif()
