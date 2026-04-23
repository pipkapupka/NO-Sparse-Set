#pragma once

#include <vector>
#include <limits>
#include <iostream>
#include <stdexcept>

namespace NO {
    constexpr unsigned int NULL_INDEX = std::numeric_limits<unsigned int>::max();

    template<typename Component, typename Allocator = std::allocator<Component>>
    class SparseSet {
    public:
        void insert(const unsigned int entity_id, const Component &component) {
            dense_entities_.push_back(entity_id);
            dense_data_.push_back(component);

            if (entity_id >= sparse_array_.size()) {
                sparse_array_.resize(entity_id + 1, NULL_INDEX);
            }

            if (!dense_entities_.empty()) {
                sparse_array_[entity_id] = dense_entities_.size() - 1;
            }
        }

        [[nodiscard]] bool contains(const unsigned int entity_id) const {
            if (entity_id >= sparse_array_.size()) {
                return false;
            }

            const auto index = sparse_array_[entity_id];
            if (index >= dense_entities_.size()) {
                return false;
            }

            return dense_entities_[index] == entity_id;
        }

        void erase(const unsigned int entity_id) {
            if (contains(entity_id)) {
                const auto index = sparse_array_[entity_id];
                if (const auto latest_index = dense_entities_.size() - 1;
                    index != latest_index) {

                    dense_entities_[index] = dense_entities_[latest_index];
                    dense_data_[index] = dense_data_[latest_index];

                    sparse_array_[dense_entities_[latest_index]] = index;
                }
                dense_entities_.pop_back();
                dense_data_.pop_back();
                sparse_array_[entity_id] = NULL_INDEX;
            }
        }

        Component* get(const unsigned int entity_id) {
            if (!contains(entity_id)) {
                return nullptr;
            }
            return &dense_data_[sparse_array_[entity_id]];
        }

        using iterator = typename std::vector<Component>::iterator;
        using const_iterator = typename std::vector<Component>::const_iterator;

        iterator begin() {
            return dense_data_.begin();
        }

        iterator end() {
            return dense_data_.end();
        }

        const_iterator begin() const {
            return dense_data_.begin();
        }

        const_iterator end() const {
            return dense_data_.end();
        }

        const_iterator cbegin() const {
            return begin();
        }

        const_iterator cend() const {
            return end();
        }

        void print() {
            for (auto i = sparse_array_.size() - 1; i > 0; i--) {
                std::cout << sparse_array_[i] << " | ";
            }
            std::cout << sparse_array_[0];
            std::cout << '\n';

            for (auto i = dense_entities_.size() - 1; i > 0; i--) {
                std::cout << dense_entities_[i] << " | ";
            }
            std::cout << dense_entities_[0];
            std::cout << '\n';

            for (auto i = dense_data_.size() - 1; i > 0; --i) {
                std::cout << dense_data_[i] << " | ";
            }
            std::cout << dense_data_[0];
            std::cout << '\n';
        }

    private:
        std::vector<Component> dense_data_;
        std::vector<unsigned int> dense_entities_;
        std::vector<unsigned int> sparse_array_;
    };
}
