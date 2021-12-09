cmake_minimum_required(VERSION 3.10.2)

project("url_parser")

include_directories(${CMAKE_CURRENT_LIST_DIR})

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} URL_PARSER_SRC_FILES)

add_library(url_parser SHARED ${URL_PARSER_SRC_FILES})