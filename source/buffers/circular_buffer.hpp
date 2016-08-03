#ifndef ODACHI_CIRCULAR_BUFFER_HPP
#define ODACHI_CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <utility>
#include <algorithm>
#include "../allocators/heap_allocator.hpp"

namespace odachi{
    namespace datastructures{
        namespace buffers{

            template<typename T, size_t N, typename TAllocator = allocators::heap_allocator>
            class circular_buffer{
            public:
                explicit circular_buffer(TAllocator allocator = allocators::heap_allocator{});
                circular_buffer(circular_buffer const& other);
                circular_buffer& operator=(circular_buffer const& other);
                void enqueue(T const& element);
                void dequeue();
                T& front();
                T const& front() const;
                T& operator[](size_t index);
                T const& operator[](size_t index) const;
                ~circular_buffer();
                size_t capacity() const;
                size_t head() const;
                size_t tail() const;
                size_t size() const;
                size_t free_slots() const;
                bool is_full() const;
                bool is_empty() const;
            private:
                TAllocator allocator_;
                T* elements_;
                size_t size_;
                size_t head_;
                size_t tail_;
            };

            template<typename T, size_t N, typename TAllocator>
            circular_buffer<T,N,TAllocator>::circular_buffer(TAllocator allocator)
                    : allocator_(std::move(allocator)),
                      elements_(reinterpret_cast<T*>(allocator_.allocate(sizeof(T) * N))),
                      size_{0},
                      head_{0},
                      tail_{0}

            {
            }

            template<typename T, size_t N, typename TAllocator>
            circular_buffer<T,N,TAllocator>::circular_buffer(circular_buffer<T,N, TAllocator> const& other)
                :   allocator_(other.allocator_),
                    elements_(reinterpret_cast<T*>(allocator_.allocate(sizeof(T) * N))),
                    size_(other.size_),
                    head_(other.head_),
                    tail_(other.tail_)
            {
                std::copy(other.elements_, other.elements_ + N, elements_);
            }

            template<typename T, size_t N, typename TAllocator>
            circular_buffer<T,N,TAllocator>::~circular_buffer() {
                allocator_.deallocate(elements_);
            }

            template<typename T, size_t N,typename TAllocator >
            circular_buffer<T,N,TAllocator>& circular_buffer<T,N,TAllocator>::operator=(circular_buffer const &other) {

                if(this == &other)
                    return *this;

                circular_buffer t{other};
                allocator_.deallocate(this->elements_);
                this->elements_ = t.elements_;
                this->size_ = t.size_;
                this->head_ = t.head_;
                this->tail_ = t.tail_;
                t.elements_ = nullptr;
                return *this;

            }

            template<typename T, size_t N, typename TAllocator>
            void circular_buffer<T,N,TAllocator>::enqueue(const T &element) {

                elements_[head_ % N] = element;
                head_ = ++head_ % N;

                if(is_full()){
                    tail_ = ++tail_ % N;
                }else{
                    ++size_;
                }
            }

            template<typename T, size_t N, typename TAllocator>
            void circular_buffer<T,N,TAllocator>::dequeue() {

                if(is_empty())
                    return;

                tail_ = ++tail_ % N;
                --size_;
            }

            template<typename T, size_t N, typename TAllocator>
            T& circular_buffer<T,N,TAllocator>::front() {
                return this->elements_[tail_];
            }

            template<typename T, size_t N, typename TAllocator>
            T const& circular_buffer<T,N,TAllocator>::front() const {
                return this->elements_[tail_];
            }

            template<typename T, size_t N, typename TAllocator>
            T& circular_buffer<T,N,TAllocator>::operator[](size_t index) {
                return this->elements_[index];
            }

            template<typename T, size_t N, typename TAllocator>
            T const & circular_buffer<T,N,TAllocator>::operator[](size_t index) const {
                return this->elements_[index];
            }

            template<typename T, size_t N, typename TAllocator>
            size_t circular_buffer<T,N,TAllocator>::capacity() const {
                return N;
            }

            template<typename T, size_t N, typename TAllocator>
            size_t circular_buffer<T,N,TAllocator>::size() const {
                return this->size_;
            }

            template<typename T, size_t N, typename TAllocator>
            size_t circular_buffer<T,N,TAllocator>::tail() const {
                return this->tail_;
            }

            template<typename T, size_t N, typename TAllocator>
            bool circular_buffer<T,N,TAllocator>::is_full() const {
                return this->size_ == N;
            }

            template<typename T, size_t N, typename TAllocator>
            bool circular_buffer<T,N,TAllocator>::is_empty() const {
                return this->size_ == 0;
            }

            template<typename T, size_t N, typename TAllocator>
            size_t circular_buffer<T,N,TAllocator>::head() const {
                return this->head_;
            }

            template<typename T, size_t N, typename TAllocator>
            size_t circular_buffer<T,N,TAllocator>::free_slots() const {
                return this->capacity() - this->size();
            }
        }
    }
}






#endif