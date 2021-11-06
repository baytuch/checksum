
cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_BUILD_TYPE Release)
project(checksum)

add_library(md5 STATIC md5.cpp)

add_executable(${PROJECT_NAME} main.cpp utils.cpp)
target_link_libraries(${PROJECT_NAME} md5)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} DESTINATION bin)

