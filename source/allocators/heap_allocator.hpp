#ifndef ODACHI_HEAP_ALLOCATOR_HPP
#define ODACHI_HEAP_ALLOCATOR_HPP

#include <cstddef>

namespace odachi{
    namespace allocators{

        class heap_allocator {
        public:

            heap_allocator() = default;
            heap_allocator(heap_allocator const&) = default;
            heap_allocator& operator=(heap_allocator const&) = default;
            heap_allocator(heap_allocator&&) = default;
            heap_allocator& operator=(heap_allocator&&) = default;
            ~heap_allocator() = default;
            void* allocate(size_t size);
            void deallocate(void* address);
        };

        void* heap_allocator::allocate(size_t size) {
            auto* address = ::operator new(size);
            return address;
        }

        void heap_allocator::deallocate(void* address) {
            ::operator delete(address);
        }

    }
}



#endif