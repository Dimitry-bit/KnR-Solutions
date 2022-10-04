cmake_minimum_required(VERSION 3.20)
project(Exercise_5_14 C)
set(CMAKE_C_STANDARD 99)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(Exercise_5_14 ${SRC_FILES})

target_include_directories(Exercise_5_14
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
