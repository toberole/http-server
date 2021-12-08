cmake_minimum_required(VERSION 3.10.2)

project("server")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/server/include)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/server/src SRC_FILES)

add_library(server SHARED ${SRC_FILES})

target_link_libraries(server 
    pthread
    http_parser
    url_parser
)