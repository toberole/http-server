include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
# if(${CMake_VERSION} VERSION_LESS 3.14)
#     include(${CMAKE_CURRENT_LIST_DIR}/cmake/add_FetchContent_MakeAvailable.cmake)
# endif()

set(LIBUV_GIT_TAG  v1.42.0)  # 指定版本
set(LIBUV_GIT_URL  https://github.com/libuv/libuv)  # 指定git仓库地址

FetchContent_Declare(
  libuv
  GIT_REPOSITORY    ${LIBUV_GIT_URL}
  GIT_TAG           ${LIBUV_GIT_TAG}
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third/libuv
)

FetchContent_MakeAvailable(libuv)
 
# FetchContent_GetProperties(libuv)
# if(NOT libuv_POPULATED)
#     FetchContent_Populate(libuv)
#     # add_library(libuv INTERFACE)
#     # target_include_directories(libuv INTERFACE ${libuv_SOURCE_DIR}/include)
#     add_subdirectory(${libuv_SOURCE_DIR})
# endif()
