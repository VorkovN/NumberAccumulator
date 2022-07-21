project(Client)
message(STATUS "building ${PROJECT_NAME}")

add_subdirectory(Interfaces)
add_subdirectory(Sources)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ClientInterfaces ClientSources)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin/apps)