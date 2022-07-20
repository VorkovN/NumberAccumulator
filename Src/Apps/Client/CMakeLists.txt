project(Client)
message(STATUS "building ${PROJECT_NAME}")

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${sources} ${headers})

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory(Tests)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin/apps)