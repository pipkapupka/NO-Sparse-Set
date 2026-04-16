#include <NextOren/SparseSet.hpp>
#include <gtest/gtest.h>

int main() {
    NO::SparseSet<int> set;
    set.insert(10, 1234);
    set.insert(20, 23465436);
    set.insert(11, 323412);
    set.insert(5, 1);

    std::cout << set.contains(11) << std::endl;
    std::cout << set.contains(12) << std::endl;
    std::cout << set.contains(1) << std::endl;
    std::cout << set.contains(5) << std::endl;
    std::cout << set.contains(1231231) << std::endl;

    std::cout << set.get(11) << std::endl;
    std::cout << set.get(12) << std::endl;
    std::cout << set.get(5) << std::endl;
    std::cout << set.get(9) << std::endl;
}
