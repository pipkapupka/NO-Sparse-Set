#pragma once

#include <algorithm>
#include <vector>
#include <limits>
#include <stdexcept>

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

            if (!dense_entities_.empty()) {
                sparse_array_[entity_id] = dense_entities_.size() - 1;
            }
        }

        [[nodiscard]] bool contains(const unsigned int entity_id) const {
            if (entity_id > sparse_array_.size()) {
                return false;
            }

            const auto index = sparse_array_[entity_id];
            if (index >= dense_data_.size()) {
                return false;
            }

            return dense_entities_[index] == entity_id;
        }

        void erase(const unsigned int entity_id) {
            if (contains(entity_id)) {
                const auto index = sparse_array_[entity_id];
                std::swap(dense_entities_[index], dense_entities_.back());
                std::swap(dense_data_[index], dense_data_.back());
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

        class Iterator {
        public:
            explicit Iterator(const typename std::vector<Component>::iterator comp) : comp_(comp) {}

            Component& operator*() {
                return *comp_;
            }

            Component* operator->() {
                return comp_;
            }

            Iterator& operator++() {
                ++comp_;
                return *this;
            }

            bool operator!=(const Iterator& rhs) const {
                return comp_ != rhs.comp_;
            }

        private:
            typename std::vector<Component>::iterator comp_;
        };

        Iterator begin() noexcept {
            return dense_data_.begin();
        }

        Iterator end() noexcept {
            return dense_data_.end();
        }

    private:
        std::vector<Component> dense_data_;
        std::vector<unsigned int> dense_entities_;
        std::vector<unsigned int> sparse_array_;
    };
}
