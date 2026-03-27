cmake_minimum_required(VERSION 4.0)
project(NO_Sparse_Set)

set(CMAKE_CXX_STANDARD 17)

add_library(SparseSet INTERFACE)
target_include_directories(SparseSet INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)
