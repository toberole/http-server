cmake_minimum_required(VERSION 3.10.2)

project("demo1")

include_directories(${CMAKE_CURRENT_LIST_DIR})

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} DEMO1_SRC_FILES)

add_executable(demo1 ${DEMO1_SRC_FILES})

target_link_libraries(demo1
        pthread
)