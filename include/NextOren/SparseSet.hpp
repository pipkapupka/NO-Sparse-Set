#pragma once

#include <algorithm>
#include <vector>
#include <limits>

namespace NO {
    constexpr unsigned int NULL_INDEX = std::numeric_limits<unsigned int>::max();

    template<typename Component, typename Allocator = std::allocator<Component>>
    class SparseSet {
    public:
        void insert(const unsigned int entity_id, const Component &component) {
            dense_entities_.push_back(entity_id);
            dense_data_.push_back(component);

            if (entity_id > sparse_array_.size()) {
                sparse_array_.resize(entity_id + 1, NULL_INDEX);
            }

            if (!dense_entities_.empty()) sparse_array_[entity_id] = dense_entities_.size() - 1;
        }

        bool contains(unsigned int entity_id) const {
            return true;
        }

        void erase(unsigned int entity_id) {

        }

        Component& get(unsigned int entity_id) {

        }

        typename std::vector<Component>::iterator begin() noexcept {};
        typename std::vector<Component>::iterator end() noexcept {};

    private:
        std::vector<Component> dense_data_;
        std::vector<unsigned int> dense_entities_;
        std::vector<unsigned int> sparse_array_;
    };
}