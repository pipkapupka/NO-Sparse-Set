#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <tuple>

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

        class Iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = std::pair<unsigned int, Component>;
            using pointer = Component*;
            using reference = std::tuple<unsigned int, Component&>;
            using iterator_category = std::random_access_iterator_tag;

            explicit Iterator(std::tuple<unsigned int*, Component*> iterator) : iter_(iterator) {}

            pointer operator->() {
                return std::get<1>(iter_);
            }

            reference operator*() {
                return {*std::get<0>(iter_), *std::get<1>(iter_)};
            }

            Iterator& operator++() {
                ++std::get<0>(iter_);
                ++std::get<1>(iter_);
                return *this;
            }

            Iterator operator++(int) {
                Iterator copy = *this;
                ++std::get<0>(iter_);
                ++std::get<1>(iter_);
                return copy;
            }

            bool operator==(const Iterator& other) {
                return std::get<0>(iter_) == std::get<0>(other.iter_) &&
                    std::get<1>(iter_) == std::get<1>(other.iter_);
            }

            bool operator!=(const Iterator& other) {
                return !(*this == other);
            }

            Iterator& operator=(const Iterator& other) {
                std::get<0>(iter_) = std::get<0>(other.iter_);
                std::get<1>(iter_) = std::get<1>(other.iter_);
                return *this;
            };

            Iterator& operator--() {
                --std::get<0>(iter_);
                --std::get<1>(iter_);
                return *this;
            }

            Iterator operator--(int) {
                Iterator copy = *this;
                --std::get<0>(iter_);
                --std::get<1>(iter_);
                return copy;
            }

            Iterator& operator+=(difference_type offset) {
                std::get<0>(iter_) += offset;
                std::get<1>(iter_) += offset;
                return *this;
            }

            Iterator& operator-=(difference_type offset) {
                std::get<0>(iter_) -= offset;
                std::get<1>(iter_) -= offset;
                return *this;
            }

            Iterator operator+(difference_type offset) {
                Iterator copy = *this;
                std::get<0>(copy.iter_) += offset;
                std::get<1>(copy.iter_) += offset;
                return copy;
            }

            friend Iterator operator+(difference_type offset, const Iterator& other) {
                Iterator copy = other;
                std::get<0>(copy.iter_) += offset;
                std::get<1>(copy.iter_) += offset;
                return copy;
            }

            Iterator operator-(difference_type offset) {
                Iterator copy = *this;
                std::get<0>(copy.iter_) -= offset;
                std::get<1>(copy.iter_) -= offset;
                return copy;
            }

            auto operator[](difference_type index) {
                return *(*this + index);
            }

            friend bool operator<(const Iterator& lhs,const Iterator& rhs) {
                return std::get<1>(lhs.iter_) < std::get<1>(rhs.iter_);
            }

            friend bool operator>(const Iterator& lhs,const Iterator& rhs) {
                return std::get<1>(lhs.iter_) > std::get<1>(rhs.iter_);
            }

            friend bool operator<=(const Iterator& lhs, const Iterator& rhs) {
                return !(lhs.iter_ > rhs.iter_);
            }

            friend bool operator>=(const Iterator& lhs, const Iterator& rhs) {
                return !(lhs.iter_ < rhs.iter_);
            }

            friend difference_type operator-(const Iterator& lhs, const Iterator& rhs) {
                return std::get<0>(lhs.iter_) - std::get<0>(rhs.iter_);
            }

            /* TODO:
             * it-> it* (✓)
             * it++ ++it (✓)
             * it == other && it != other (✓)
             * iterator (✓)
             * operator= (✓)
             * it-- --it (✓)
             * it += n; it -= n (✓)
             * it + n; n + it; it - n; (✓)
             * it[n] (✓)
             * it1 - it2 (✓)
             * < > <= >= (✓)
             */

        private:
            std::tuple<unsigned int*, Component*> iter_;
        };

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
