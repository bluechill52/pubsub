#pragma once
#include <array>
#include <cstddef>

template <typename T, std::size_t Capacity>
class RingBuffer {
public:
    // Returns false if an overwrite occurred (full buffer)
    bool push(const T& item) {
        bool overwritten = false;
        if (size_ == Capacity) {
            // Overwrite oldest — advance head
            head_ = (head_ + 1) % Capacity;
            overwritten = true;
        } else {
            ++size_;
        }
        buffer_[tail_] = item;
        tail_ = (tail_ + 1) % Capacity;
        return !overwritten;
    }

    T front() const {
        return buffer_[head_];
    }

    void pop() {
        head_ = (head_ + 1) % Capacity;
        --size_;
    }

    bool empty() const { return size_ == 0; }
    bool full()  const { return size_ == Capacity; }
    std::size_t size() const { return size_; }

private:
    std::array<T, Capacity> buffer_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};