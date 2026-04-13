include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(SparseSet_Tests test_main.cpp)

target_link_libraries(SparseSet_Tests PRIVATE
        NO-Sparse-Set
        GTest::gtest_main
)

include(GoogleTest)
include(CTest)
gtest_discover_tests(SparseSet_Tests)