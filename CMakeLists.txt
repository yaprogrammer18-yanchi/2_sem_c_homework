cmake_minimum_required(VERSION 3.25)
project(C_HW C)
add_compile_options(-Wall -Wextra -pedantic -fsanitize=address)
add_link_options(-fsanitize=address)

add_library(TandC src/graphs/TownsCountries.c)
add_library(MinHeap src/graphs/minHeap.c)
add_library(features src/graphs/features.c)

add_executable(testsForGraphsTask src/graphs/tests.c)
add_executable(graphsTask src/graphs/main.c)

target_link_libraries(testsForGraphsTask PRIVATE TandC)
target_link_libraries(testsForGraphsTask PRIVATE MinHeap)
target_link_libraries(testsForGraphsTask PRIVATE features)
target_link_libraries(MinHeap PRIVATE TandC)
target_link_libraries(features PRIVATE MinHeap)
target_link_libraries(graphsTask PRIVATE TandC)
target_link_libraries(graphsTask PRIVATE features)



