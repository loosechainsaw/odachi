#include <iostream>
#include "allocators/heap_allocator.hpp"
#include "buffers/circular_buffer.hpp"

int main() {

    using namespace odachi::allocators;
    using namespace odachi::datastructures::buffers;

    heap_allocator allocator;
    circular_buffer<int, heap_allocator, 10> buffer(allocator);

    for(auto i = 0; i < 50; ++i){
        buffer.push_back(i);
    }

    decltype(buffer) b = buffer;
    decltype(buffer) c(allocator);
    c = b;

    for(auto i = 0; i < 10; ++i){
        std::cout << "Index: " << i << ", Contains: " << c[i] << "\n";
    }

    std::cout << "Capacity: " << b.capacity() << ", Size: " << b.size() <<
              ", Position: " << b.position() << ", Free Slots: " << b.free_slots() << "\n";

    return 0;
}