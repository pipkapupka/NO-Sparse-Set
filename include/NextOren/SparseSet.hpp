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
            if (contains(entity_id)) return;
            /* Добавляем данные в конец массива для плотности и кэш-локальности*/
            dense_entities_.push_back(entity_id);
            dense_data_.push_back(component);

            if (entity_id >= sparse_array_.size()) {
                sparse_array_.resize(entity_id + 1, NULL_INDEX);
            }

            /* Связываем sparse_array с только что добавленным в конец entity_id */
            sparse_array_[entity_id] = dense_entities_.size() - 1;
        }

        [[nodiscard]] bool contains(const unsigned int entity_id) const {
            /* Если entity_id больше чем размер разряженного массива, значит такого энтити в плотных нет */
            if (entity_id >= sparse_array_.size()) {
                return false;
            }

            const auto index = sparse_array_[entity_id]; // Получаем номер ячейки в плотном массиве, хранящий entity_id

            /* Индекс должен быть меньше чем размер плотного массива*/
            if (index >= dense_entities_.size()) {
                return false;
            }

            /* Сравниваем номер ячейки с нужным нам содержимым и возвращаем результат */
            return dense_entities_[index] == entity_id;
        }

        void erase(const unsigned int entity_id) {
            if (contains(entity_id)) {
                const auto index = sparse_array_[entity_id]; // Получаем номер ячейки в плотном массиве, хранящий entity_id

                /*
                 * Получаем номер последней ячейки в плотном массиве, куда будем `swap-and-pop` элемент
                 * Также проверяем что мы не собираемся `swap-and-pop` уже последний элемент
                 */
                if (const auto latest_index = dense_entities_.size() - 1;
                    index != latest_index) {

                    /* Перезаписываем содержимое индексов на содержимое последних элемента плотных массивов*/
                    dense_entities_[index] = dense_entities_[latest_index];
                    dense_data_[index] = dense_data_[latest_index];

                    /* Берём сущности, которую переставили и делаем её индекс актуальной */
                    sparse_array_[dense_entities_[latest_index]] = index;
                }

                /* Удаляем свапнутые элементы с конца за O(1) и очищаем маппинг в разряженном массиве */
                dense_entities_.pop_back();
                dense_data_.pop_back();
                sparse_array_[entity_id] = NULL_INDEX;
            }
        }

        Component* get(const unsigned int entity_id) {
            if (!contains(entity_id)) {
                return nullptr;
            }
            /* Возвращаем указатель на компонент внутри плотного массива компонентов по номеру ячейки */
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
