cmake_minimum_required(VERSION 3.20)

project(fastdds_modern_cpp VERSION 1 LANGUAGES CXX)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")

add_subdirectory("examples")
