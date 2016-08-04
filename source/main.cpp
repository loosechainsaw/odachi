#include <iostream>
#include "allocators/heap_allocator.hpp"
#include "buffers/circular_buffer.hpp"
#include "buffers/lru_cache.hpp"

int main() {

    using namespace odachi::allocators;
    using namespace odachi::datastructures::buffers;

    lru_cache<int,int> cache(4);
    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);
    cache.put(4,4);
    cache.put(5,5);

    bool c = cache.contains(1);
    bool d = cache.contains(5);


    return 0;
}