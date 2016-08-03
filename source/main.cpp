#include <iostream>
#include "allocators/heap_allocator.hpp"
#include "buffers/circular_buffer.hpp"

int main() {

    using namespace odachi::allocators;
    using namespace odachi::datastructures::buffers;

    heap_allocator allocator;
    circular_buffer<int, 10> buffer;

    for(auto i = 0; i < 50; ++i){
        buffer.enqueue(i);
    }

    decltype(buffer) b = buffer;
    decltype(buffer) c(allocator);
    c = b;

    c.dequeue();

    for(auto i = 0; i < 10; ++i){
        std::cout << "Index: " << i << ", Contains: " << c[i] << "\n";
    }

    std::cout << "Capacity: " << c.capacity() << ", Size: " << c.size() <<
              ", Position: " << c.head() << ", Free Slots: " << c.free_slots() << "\n";

    return 0;
}