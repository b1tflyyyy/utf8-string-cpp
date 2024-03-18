cmake_minimum_required(VERSION 3.14)

set(LIBRARY_NAME utf8-string-lib)

set(SOURCES utf8_string.cpp)
set(HEADERS utf8_string.hpp)

add_library(${LIBRARY_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ./)