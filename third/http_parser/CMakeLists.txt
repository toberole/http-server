cmake_minimum_required(VERSION 3.10.2)

project("http_parser")

include_directories(${CMAKE_CURRENT_LIST_DIR})

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} HTTP_PARSER_SRC_FILES)

add_library(http_parser SHARED ${HTTP_PARSER_SRC_FILES})