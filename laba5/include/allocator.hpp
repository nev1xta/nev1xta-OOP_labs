#pragma once

#include <memory>
#include <list>
#include <algorithm>        
#include <functional>           
#include <iterator>

class Allocator : public std::pmr::memory_resource {
public:
    Allocator();
    ~Allocator() noexcept;
private:
    void do_allocate(size_t bytes);
    void do_deallocate(void* p, size_t bytes);
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
    std::list<std::pair<void*, std::size_t>> chunks;
};