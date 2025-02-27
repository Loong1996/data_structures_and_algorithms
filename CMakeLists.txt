cmake_minimum_required(VERSION 3.10)

project(DataStucturesAndAlgorithms)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/data_structures)

aux_source_directory(. SRC_LIST)

add_executable(DataStucturesAndAlgorithms ${SRC_LIST})