#ifndef ODACHI_CIRCULAR_BUFFER_HPP
#define ODACHI_CIRCULAR_BUFFER_HPP

#include <cstddef>
#include <utility>
#include <algorithm>

namespace odachi{
    namespace datastructures{
        namespace buffers{

            template<typename T, typename TAllocator, size_t N>
            class circular_buffer{
            public:
                explicit circular_buffer(TAllocator allocator);
                circular_buffer(circular_buffer const& other);
                circular_buffer& operator=(circular_buffer const& other);
                void push_back(T const& element);
                T& operator[](size_t index);
                T const& operator[](size_t index) const;
                ~circular_buffer();
                size_t capacity() const;
                size_t position() const;
                size_t size() const;
                size_t free_slots() const;
            private:
                TAllocator allocator_;
                T* elements_;
                size_t size_;
                size_t position_;
            };

            template<typename T, typename TAllocator, size_t N>
            circular_buffer<T,TAllocator,N>::circular_buffer(TAllocator allocator)
                    : allocator_(std::move(allocator)),
                      elements_(reinterpret_cast<T*>(allocator_.allocate(sizeof(T) * N))),
                      size_{0},
                      position_{0}

            {
            }

            template<typename T, typename TAllocator, size_t N>
            circular_buffer<T,TAllocator,N>::circular_buffer(circular_buffer<T,TAllocator,N> const& other)
                :   allocator_(other.allocator_),
                    elements_(reinterpret_cast<T*>(allocator_.allocate(sizeof(T) * N))),
                    size_{other.size_},
                    position_{other.position_}
            {
                std::copy(other.elements_, other.elements_ + N, elements_);
            }

            template<typename T, typename TAllocator, size_t N>
            circular_buffer<T,TAllocator,N>::~circular_buffer() {
                allocator_.deallocate(elements_);
            }

            template<typename T, typename TAllocator, size_t N>
            circular_buffer<T, TAllocator, N>& circular_buffer<T,TAllocator,N>::operator=(circular_buffer const &other) {

                if(this == &other)
                    return *this;

                circular_buffer t{other};
                allocator_.deallocate(this->elements_);
                this->elements_ = t.elements_;
                this->size_ = t.size_;
                this->position_ = t.position_;
                t.elements_ = nullptr;
                return *this;

            }

            template<typename T, typename TAllocator, size_t N>
            void circular_buffer<T,TAllocator,N>::push_back(const T &element) {
                elements_[position_ % N] = element;

                position_ = ++position_ % N;

                if(size_ < N)
                    ++size_;

            }

            template<typename T, typename TAllocator, size_t N>
            T& circular_buffer<T,TAllocator,N>::operator[](size_t index) {
                return this->elements_[index];
            }

            template<typename T, typename TAllocator, size_t N>
            T const & circular_buffer<T, TAllocator,N>::operator[](size_t index) const {
                return this->elements_[index];
            }

            template<typename T, typename TAllocator, size_t N>
            size_t circular_buffer<T,TAllocator,N>::capacity() const {
                return N;
            }

            template<typename T, typename TAllocator, size_t N>
            size_t circular_buffer<T, TAllocator,N>::size() const {
                return this->size_;
            }

            template<typename T, typename TAllocator, size_t N>
            size_t circular_buffer<T, TAllocator,N>::position() const {
                return this->position_;
            }

            template<typename T, typename TAllocator, size_t N>
            size_t circular_buffer<T, TAllocator,N>::free_slots() const {
                return this->capacity() - this->size();
            }
        }
    }
}






#endif