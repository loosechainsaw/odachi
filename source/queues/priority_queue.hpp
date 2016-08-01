#ifndef ODACHI_PRIORITY_QUEUE_HPP
#define ODACHI_PRIORITY_QUEUE_HPP

#include <cstddef>


namespace odachi{
    namespace datastructures{
        namespace queues{

            template<typename T, typename TAllocator, size_t N>
            class priority_queue{
            public:
                priority_queue(TAllocator allocator);
                priority_queue(priority_queue const& ) = default;
                priority_queue& operator=(priority_queue) = default;
                priority_queue(priority_queue&&) = default;
                priority_queue& operator=(priority_queue&&) = default;
                ~priority_queue();
            private:
                TAllocator allocator_;
                T* elements_;
                size_t size_;
            };

        }
    }
}

#endif