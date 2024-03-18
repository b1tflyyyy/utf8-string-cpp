cmake_minimum_required(VERSION 3.14)

project(utf8_string LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -O0)

add_subdirectory(source)
add_subdirectory(utf8-string-lib)