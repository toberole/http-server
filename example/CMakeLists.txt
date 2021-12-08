cmake_minimum_required(VERSION 3.10.2)

project("example")

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_LIST_DIR}/server/include)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SRC_FILES)

add_executable(example ${SRC_FILES})

target_link_libraries(example 
    pthread
    server
    http_parser
    url_parser
)