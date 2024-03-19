cmake_minimum_required(VERSION 3.14)

project(Tests LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    main_test.cpp
    utf8_string_test.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_link_options(-pthread)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

set(BINARY_NAME tests${CMAKE_PROJECT_NAME})
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        utf8-string-lib
        GTest::gtest
        GTest::gmock
)