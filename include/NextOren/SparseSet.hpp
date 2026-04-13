#pragma once

#include <algorithm>
#include <vector>
#include <limits>

namespace NO {
    constexpr unsigned int NULL_INDEX = std::numeric_limits<unsigned int>::max();

    template<typename Component, typename Allocator = std::allocator<Component>>
    class SparseSet {
    public:
        void insert(unsigned int entity_id, const Component &component) {

        }

        bool contains(unsigned int entity_id) const;
        void erase(unsigned int entity_id);
        Component& get(unsigned int entity_id);
        std::vector<Component>::iterator begin() noexcept;
        std::vector<Component>::iterator end() noexcept;

    private:
        std::vector<Component> dense_data_;
        std::vector<unsigned int> dense_entities_;
        std::vector<unsigned int> sparse_array_;
    };
}