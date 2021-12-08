cmake_minimum_required(VERSION 3.10.2)

project("cpp-http-server")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/http_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/url_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/example)