project(ServerSources)
message(STATUS "building ${PROJECT_NAME}")

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${PROJECT_NAME} ServerInterfaces Libs)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})






