cmake_minimum_required(VERSION 3.8)
project(clion)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c coins.c common.c common.h coins.h test_coins.c test_coins.h kruskal.c kruskal.h test_kruskal.c test_kruskal.h)
add_executable(clion ${SOURCE_FILES})