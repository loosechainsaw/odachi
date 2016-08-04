#ifndef ODACHI_DOUBLE_ENDED_LINKED_LIST_HPP
#define ODACHI_DOUBLE_ENDED_LINKED_LIST_HPP


#include "../allocators/heap_allocator.hpp"

namespace odachi {
    namespace datastructures {
        namespace lists {

            template<typename T>
            class double_ended_linked_list{
            public:
                double_ended_linked_list();
                double_ended_linked_list(double_ended_linked_list const& other);
                double_ended_linked_list& operator=(double_ended_linked_list const& other);
                double_ended_linked_list(double_ended_linked_list&& other);
                double_ended_linked_list& operator=(double_ended_linked_list&& other);
                void push_front(T const& element);
                void push_front(T&& element);
                void push_back(T const& element);
                void push_back(T&& element);
                void remove(T const& element);
                void remove_at(T const& element);
                T& front();
                T const& front() const;
                T& back();
                T const& back() const;
                T& at(size_t index);
                T const& at(size_t index) const;
                size_t size() const;
                bool is_empty() const;
                ~double_ended_linked_list();
            private:

                struct node{
                    T value;
                    node* next;
                };

                node* head_;
                node* tail_;
                size_t size_;
            };

            template<typename T>
            double_ended_linked_list<T>::double_ended_linked_list()
                : head_{nullptr},
                  tail_{nullptr},
                  size_{0}
            {
            }

            template<typename T>
            double_ended_linked_list<T>::~double_ended_linked_list(){
                if(is_empty() )
                    return;

                while(tail_){
                    auto next = tail_->next;
                    delete tail_;
                    tail_ = next;
                }

            }

            template<typename T>
            T& double_ended_linked_list<T>::front() {
               return head_->value;
            }

            template<typename T>
            T const& double_ended_linked_list<T>::front() const {
                return head_->value;
            }

            template<typename T>
            T& double_ended_linked_list<T>::back() {
                return tail_->value;
            }

            template<typename T>
            T const& double_ended_linked_list<T>::back() const {
                return tail_->value;
            }

            template<typename T>
            T& double_ended_linked_list<T>::at(size_t index) {

                node* result{tail_};

                for(auto i = 0; i <= index; ++i){
                    result = result->next;
                }

                return result->value;
            }

            template<typename T>
            T const& double_ended_linked_list<T>::at(size_t index) const {
                node* result{tail_};

                for(auto i = 0; i <= index; ++i){
                    result = result->next;
                }

                return result->value;
            }

            template<typename T>
            size_t double_ended_linked_list<T>::size() const {
                return this->size_;
            }

            template<typename T>
            bool double_ended_linked_list<T>::is_empty() const {
                return this->size_ != 0;
            }
        }
    }
}

#endif