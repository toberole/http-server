cmake_minimum_required(VERSION 3.10.2)

project("http_parser")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

aux_source_directory(${CMAKE_CURRENT_LIST_DIR})
aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SRC_FILES)

add_library(http_parser SHARED ${SRC_FILES})