cmake_minimum_required(VERSION 3.8)
project(clion)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c coins.c common.c common.h coins.h test_coins.c test_coins.h kruskal.c kruskal.h test_kruskal.c test_kruskal.h activity_selection.c activity_selection.h test_activity_selection.c test_activity_selection.h fractional_knapsack.c fractional_knapsack.h test_fractional_knapsack.c test_fractional_knapsack.h task_scheduling.c task_scheduling.h test_task_scheduling.c test_task_scheduling.h)
add_executable(clion ${SOURCE_FILES})