cmake_minimum_required(VERSION 3.5)
project(odachi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp buffers/circular_buffer.hpp allocators/heap_allocator.hpp queues/priority_queue.hpp allocators/stack_allocator.hpp buffers/lru_cache.hpp lists/double_ended_linked_list.hpp)
add_executable(odachi ${SOURCE_FILES})