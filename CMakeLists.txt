cmake_minimum_required(VERSION 3.14)

project(utf8-string-cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -O0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(source)
add_subdirectory(utf8-string-lib)

add_subdirectory(googletest-1.14.0)
add_subdirectory(tests)