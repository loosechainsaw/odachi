#ifndef ODACHI_LRU_CACHE_HPP
#define ODACHI_LRU_CACHE_HPP

#include <cstddef>
#include <utility>
#include <unordered_map>
#include <list>
#include <algorithm>

namespace odachi {
    namespace datastructures {
        namespace buffers {

            template<typename K, typename T>
            class lru_cache {
            public:
                lru_cache(size_t capacity);
                lru_cache(lru_cache const&) = default;
                lru_cache(lru_cache&&) = default;
                lru_cache& operator=(lru_cache const&) = default;
                lru_cache& operator=(lru_cache&&) = default;
                void put(K const& key, T const& value);
                T& get(K const& key);
                T const& get(K const& key) const;
                bool is_full() const;
                bool is_empty() const;
                bool contains(K const& key) const;
                size_t capacity() const;
                size_t size() const;
                ~lru_cache() = default;
            private:
                size_t capacity_;
                size_t size_;
                std::unordered_map<K,T> elements_;
                std::list<K> history_;
            };

            template<typename K, typename T>
            lru_cache<K,T>::lru_cache(size_t capacity)
                : capacity_{capacity},
                  size_{0},
                  elements_(capacity),
                  history_{}
            {
            }

            template<typename K, typename T>
            void lru_cache<K,T>::put(K const& key, T const& value){

                if(this->is_full()){
                    auto front = this->history_.front();
                    auto it = this->elements_.find (front);
                    this->elements_.erase (it);
                    this->history_.pop_front();
                }else{
                    ++size_;
                }

                this->history_.push_back(key);
                this->elements_[key] = value;
            }

            template<typename K, typename T>
            T& lru_cache<K,T>::get(K const& key){
                return this->elements_[key];
            }

            template<typename K, typename T>
            T const& lru_cache<K,T>::get(K const& key) const{
                return this->elements_[key];
            }

            template<typename K, typename T>
            size_t lru_cache<K,T>::capacity() const{
                return this->capacity_;
            }

            template<typename K, typename T>
            size_t lru_cache<K,T>::size() const{
                return this->size_;
            }

            template<typename K, typename T>
            bool lru_cache<K,T>::is_empty() const{
                return this->size_ == 0;
            }

            template<typename K, typename T>
            bool lru_cache<K,T>::is_full() const{
                return this->size_ == this->capacity_;
            }

            template<typename K, typename T>
            bool lru_cache<K,T>::contains(K const& key) const{
                auto it = this->elements_.find(key);
                return it != this->elements_.end();
            }
        }
    }
}

#endif