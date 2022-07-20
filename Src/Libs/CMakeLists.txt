project(Libs)
message(STATUS "building ${PROJECT_NAME}")

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory(Tests)
endif()