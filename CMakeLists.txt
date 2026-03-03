cmake_minimum_required(VERSION 3.10)
project(using_hash_table)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCE_FILES "src/*.c")

add_executable(a.out ${SOURCE_FILES})
target_include_directories(a.out PRIVATE include)