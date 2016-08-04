#ifndef ODACHI_STACK_ALLOCATOR_HPP
#define ODACHI_STACK_ALLOCATOR_HPP

#include <cstddef>

namespace odachi{
    namespace allocators{

        class stack_allocator {
        public:
            stack_allocator() = default;
            stack_allocator(char* const block);
            stack_allocator(stack_allocator const&) = default;
            stack_allocator& operator=(stack_allocator const&) = default;
            stack_allocator(stack_allocator&&) = default;
            stack_allocator& operator=(stack_allocator&&) = default;
            ~stack_allocator() = default;
            void* allocate(size_t size);
            void deallocate(void* address);
        private:
            char* block_;
        };

        stack_allocator::stack_allocator(char *const block) : block_{block} {

        }

        void* stack_allocator::allocate(size_t size) {
            return block_;
        }

        void stack_allocator::deallocate(void* address) {

        }

    }
}

#endif