cmake_minimum_required(VERSION 3.10.2)

project("server")

set(CMAKE_CXX_STANDARD 11)

message(${CMAKE_CURRENT_LIST_DIR})

include_directories(${CMAKE_SOURCE_DIR}/third/http_parser)
include_directories(${CMAKE_SOURCE_DIR}/third/url_parser)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src SERVER_SRC_FILES)

add_library(http_server SHARED ${SERVER_SRC_FILES} include/Util.h src/Util.cpp src/HttpServletRequest.cpp include/HttpServletRequest.h src/HttpServlet.cpp include/HttpServlet.h src/HttpServletResponse.cpp include/HttpServletResponse.h)

target_link_libraries(http_server 
    pthread
    url_parser
    http_parser
)