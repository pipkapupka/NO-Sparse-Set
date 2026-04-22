#include <NextOren/SparseSet.hpp>
#include <gtest/gtest.h>

int main() {
    NO::SparseSet<int> set;
    set.insert(10, 1234);
    set.insert(20, 23465436);
    set.insert(11, 323412);
    set.insert(5, 1);

    auto const const_set = set;

    // std::cout << set.contains(11) << std::endl;
    // std::cout << set.contains(12) << std::endl;
    // std::cout << set.contains(1) << std::endl;
    // std::cout << set.contains(5) << std::endl;
    // std::cout << set.contains(1231231) << std::endl;

    // std::cout << set.get(11) << std::endl;
    // std::cout << set.get(12) << std::endl;
    // std::cout << set.get(5) << std::endl;
    // std::cout << set.get(9) << std::endl;

    // set.print();

    // set.erase(11);

    // std::cout << "--------------" << std::endl;
    // std::cout << set.get(11) << std::endl;
    // std::cout << set.get(5) << std::endl;
    // std::cout << set.get(10) << std::endl;
    // std::cout << set.get(20) << std::endl;

    set.print();

    // for (auto [first, second] : const_set) {
    //     std::cout << second << std::endl;
    // }
    //
    // auto it = set.begin();
    // NO::SparseSet<int>::const_iterator it_c = it;
    // for (auto [first, second] : const_set) {
    //     first = 1;
    // }
}
