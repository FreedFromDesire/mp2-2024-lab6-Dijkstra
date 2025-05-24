set(target dijkstra_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_executable(${target} ${srcs} ${hdrs} "test_graph.cpp" "test_heap.cpp")
target_link_libraries(${target} gtest)
