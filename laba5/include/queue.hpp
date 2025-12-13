#pragma once

#include<deque>
#include <allocator.hpp>

template<typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class Queue {
public:
    class iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

        private:
            typename std::deque<T, Allocator>::iterator m_it;

        public:
            iterator(typename std::deque<T, Allocator>::iterator it) : m_it(it) {}

            reference operator*() const { return *m_it; }
            pointer operator->() const { return &(*m_it); }

            iterator& operator++() { ++m_it; return *this; }
            iterator operator++(int) { iterator tmp = *this; ++m_it; return tmp; }

            iterator& operator--() { --m_it; return *this; }
            iterator operator--(int) { iterator tmp = *this; --m_it; return tmp; }

            iterator& operator+=(difference_type n) { m_it += n; return *this; }
            iterator operator+(difference_type n) const { return iterator(m_it + n); }

            iterator& operator-=(difference_type n) { m_it -= n; return *this; }
            iterator operator-(difference_type n) const { return iterator(m_it - n); }

            difference_type operator-(const iterator& other) const { return m_it - other.m_it; }

            reference operator[](difference_type n) const { return m_it[n]; }

            bool operator==(const iterator& other) const { return m_it == other.m_it; }
            bool operator!=(const iterator& other) const { return m_it != other.m_it; }
            bool operator<(const iterator& other) const { return m_it < other.m_it; }
            bool operator>(const iterator& other) const { return m_it > other.m_it; }
            bool operator<=(const iterator& other) const { return m_it <= other.m_it; }
            bool operator>=(const iterator& other) const { return m_it >= other.m_it; }
        };

        class const_iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const T;
            using difference_type = std::ptrdiff_t;
            using pointer = const T*;
            using reference = const T&;

        private:
            typename std::deque<T, Allocator>::const_iterator m_it;

        public:
            const_iterator(typename std::deque<T, Allocator>::const_iterator it) : m_it(it) {}
            const_iterator(const iterator& it) : m_it(it.m_it) {}

            reference operator*() const { return *m_it; }
            pointer operator->() const { return &(*m_it); }

            const_iterator& operator++() { ++m_it; return *this; }
            const_iterator operator++(int) { const_iterator tmp = *this; ++m_it; return tmp; }

            const_iterator& operator--() { --m_it; return *this; }
            const_iterator operator--(int) { const_iterator tmp = *this; --m_it; return tmp; }

            const_iterator& operator+=(difference_type n) { m_it += n; return *this; }
            const_iterator operator+(difference_type n) const { return const_iterator(m_it + n); }

            const_iterator& operator-=(difference_type n) { m_it -= n; return *this; }
            const_iterator operator-(difference_type n) const { return const_iterator(m_it - n); }

            difference_type operator-(const const_iterator& other) const { return m_it - other.m_it; }

            reference operator[](difference_type n) const { return m_it[n]; }

            bool operator==(const const_iterator& other) const { return m_it == other.m_it; }
            bool operator!=(const const_iterator& other) const { return m_it != other.m_it; }
            bool operator<(const const_iterator& other) const { return m_it < other.m_it; }
            bool operator>(const const_iterator& other) const { return m_it > other.m_it; }
            bool operator<=(const const_iterator& other) const { return m_it <= other.m_it; }
            bool operator>=(const const_iterator& other) const { return m_it >= other.m_it; }
        };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Queue();
    Queue(const Queue& other);
    Queue(const std::initializer_list<T>& list);
    Queue(Queue&& other) noexcept;
    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    ~Queue() noexcept;

    void push(const T& value);
    void push(T&& value);
    void pop();

    T& front();
    const T& front() const;
    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    bool empty() const;
    size_t size() const;

    iterator begin() noexcept { return iterator(queue.begin()); }
    iterator end() noexcept { return iterator(queue.end()); }

    const_iterator begin() const noexcept { return const_iterator(queue.begin()); }
    const_iterator end() const noexcept { return const_iterator(queue.end()); }

    const_iterator cbegin() const noexcept { return const_iterator(queue.cbegin()); }
    const_iterator cend() const noexcept { return const_iterator(queue.cend()); }

    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }
private:
    std::deque<T, Allocator> queue;
};

#include"queue.ipp"