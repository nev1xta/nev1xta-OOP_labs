#include<queue.hpp>

template<typename T, typename Allocator>
Queue<T, Allocator>::Queue() {
    queue = std::deque<T, Allocator>();
}

template<typename T, typename Allocator>
Queue<T, Allocator>::Queue(const std::initializer_list<T>& list) {
    queue = std::deque<T, Allocator>(list);
}

template<typename T, typename Allocator>
Queue<T, Allocator>::~Queue() noexcept = default;

template<typename T, typename Allocator>
Queue<T, Allocator>::Queue(const Queue& other) {
    queue = other.queue;
}

template<typename T, typename Allocator>
Queue<T, Allocator>& Queue<T, Allocator>::operator=(const Queue& other) {
    queue = other.queue;
    return *this;
}

template<typename T, typename Allocator>
Queue<T, Allocator>::Queue(Queue&& other) noexcept {
    queue = std::move(other.queue);
}

template<typename T, typename Allocator>
Queue<T, Allocator>& Queue<T, Allocator>::operator=(Queue&& other) noexcept {
    queue = std::move(other.queue);
    return *this;
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::push(const T& value) {
    queue.push_back(value);
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::push(T&& value) {
    queue.push_back(std::move(value));
}

template<typename T, typename Allocator>
void Queue<T, Allocator>::pop() {
    queue.pop_front();
}

template<typename T, typename Allocator>
T& Queue<T, Allocator>::front() {
    return queue.front();
}

template<typename T, typename Allocator>
const T& Queue<T, Allocator>::front() const {
    return queue.front();
}

template<typename T, typename Allocator>
T& Queue<T, Allocator>::operator[](size_t i) {
    return queue[i];
}

template<typename T, typename Allocator>
const T& Queue<T, Allocator>::operator[](size_t i) const {
    return queue[i];
}

template<typename T, typename Allocator>
bool Queue<T, Allocator>::empty() const {
    return queue.empty();
}

template<typename T, typename Allocator>
size_t Queue<T, Allocator>::size() const {
    return queue.size();
}