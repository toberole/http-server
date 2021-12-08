cmake_minimum_required(VERSION 3.10.2)

project("server")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/third)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SRC_FILES)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/http_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/url_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/example)

add_library(server SHARED ${SRC_FILES})

target_link_libraries(server 
    pthread
    http_parser
    url_parser
)