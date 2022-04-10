cmake_minimum_required(VERSION 3.20)
project(Exercise_1_17 C)
set(CMAKE_C_STANDARD 99)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(Exercise_1_17 ${SRC_FILES})

target_include_directories(Exercise_1_17
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
