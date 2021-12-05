cmake_minimum_required(VERSION 3.10.2)

project("server")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third/parser)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/example SRC_FILES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC_FILES)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/third/parser SRC_FILES)

add_library(server SHARED ${SRC_FILES})

target_link_libraries(server pthread)

add_executable(example ${SRC_FILES})

target_link_libraries(example pthread)