#ifndef ODACHI_PRIORITY_QUEUE_HPP
#define ODACHI_PRIORITY_QUEUE_HPP

#include <cstddef>
#include "../allocators/heap_allocator.hpp"

namespace odachi{
    namespace datastructures{
        namespace queues{

            template<typename T, size_t N, typename TAllocator = allocators::heap_allocator>
            class priority_queue{
            public:
                explicit priority_queue(TAllocator allocator = allocators::heap_allocator{} );
                priority_queue(priority_queue const& ) = default;
                priority_queue& operator=(priority_queue) = default;
                priority_queue(priority_queue&&) = default;
                priority_queue& operator=(priority_queue&&) = default;
                void push_back(T const& element);
                T& top();
                T const& top() const;
                void pop();
                ~priority_queue();

                template<typename InputIterator>
                static priority_queue from(InputIterator start, InputIterator end);
            private:
                void heapify(size_t index);
                size_t left() const;
                size_t right() const;
                size_t parent();
                TAllocator allocator_;
                T* elements_;
                size_t size_;
            };

            template<typename T,

        }
    }
}

#endif