cmake_minimum_required(VERSION 3.22)
project(NumberAccumulator)

set(CMAKE_CXX_STANDARD 17)

message("Apps building:")
add_subdirectory(Src)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message("Test building:")
    find_package (GTest)
    add_subdirectory(Tests)
endif()
