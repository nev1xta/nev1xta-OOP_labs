#include<allocator.hpp>

Allocator::~Allocator() {
    for (auto& chunk : chunks) {
        std::free(chunk.first);
    }
    chunks.clear();
}

Allocator::Allocator() = default;

void Allocator::do_allocate(size_t bytes) {
    std::pair<void*, std::size_t> chunk = std::make_pair(std::malloc(bytes), bytes);
    chunks.push_back(chunk);
}

void Allocator::do_deallocate(void* p, size_t bytes) {
    std::pair<void*, std::size_t> chunk = std::make_pair(p, bytes);
    auto it = std::find(chunks.begin(), chunks.end(), chunk);
    if (it != chunks.end()) {
        ::operator delete[](chunk.first);
        chunks.erase(it);
    }
}

bool Allocator::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}