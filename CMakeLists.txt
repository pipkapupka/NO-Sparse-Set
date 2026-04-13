cmake_minimum_required(VERSION 4.0)
project(NO-Sparse-Set
        VERSION 1.0.0
        DESCRIPTION "Sparse set implementation for NextOren needs"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_library(NO-Sparse-Set INTERFACE)
target_include_directories(NO-Sparse-Set INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_subdirectory(tests)
