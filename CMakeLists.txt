cmake_minimum_required(VERSION 3.10.2)

project("server")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/example SRC_FILES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC_FILES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/third SRC_FILES)

add_library(server SHARED ${SRC_FILES})

add_executable(example ${SRC_FILES})