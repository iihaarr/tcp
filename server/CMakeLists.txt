cmake_minimum_required(VERSION 3.20)

project(tsp_server)

file(GLOB_RECURSE SOURCES ./src/*.cpp)
file(GLOB_RECURSE HEADERS ./src/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} main.cpp)

target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)