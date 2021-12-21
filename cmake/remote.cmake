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
)

FetchContent_MakeAvailable(libuv)

include_directories()