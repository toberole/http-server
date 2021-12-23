cmake_minimum_required(VERSION 3.11)
# cmake_minimum_required(VERSION 3.14.7)
# cmake_minimum_required(VERSION 3.10.2)
project("cpp-http-server")

include(${CMAKE_CURRENT_LIST_DIR}/cmake/base.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/remote.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/http_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third/url_parser)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/server)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/example)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/demo1)