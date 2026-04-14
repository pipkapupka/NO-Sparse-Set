#include <NextOren/SparseSet.hpp>
#include <gtest/gtest.h>

int main() {
    NO::SparseSet<int> set;
    set.insert(10, 1234);
    set.insert(20, 23465436);
    set.insert(11, 323412);
    set.insert(5, 1);
}
