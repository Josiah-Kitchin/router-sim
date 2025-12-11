
#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstring> 

template <typename T> class FixedQueue
{
  public:
    FixedQueue(size_t n)
    {
        _items    = new T[n];
        _max_size = n;
        _capacity = n;
    }

    ~FixedQueue() { delete _items; }
    FixedQueue(const FixedQueue& other)
    {
        _items     = new T[other._max_size];
        _max_size  = other._max_size;
        _num_items = other._num_items;
        _front     = other._front;
        _capacity  = other._capacity;
        memcpy(_items, other._items, other._max_size);
    }
    void operator=(const FixedQueue& other)
    {
        _items     = new T[other._max_size];
        _max_size  = other._max_size;
        _num_items = other._num_items;
        _front     = other._front;
        _capacity  = other._capacity;
        memcpy(_items, other._items, other._max_size);
    }
    FixedQueue(FixedQueue&& other)
    {
        if (this == &other)
            return;
        _items       = other._items;
        _max_size    = other._max_size;
        _num_items   = other._num_items;
        _front       = other._front;
        _capacity    = other._capacity;
        other._items = nullptr;
    }
    void operator=(FixedQueue&& other)
    {
        if (this == &other)
            return;
        _items       = other._items;
        _max_size    = other._max_size;
        _num_items   = other._num_items;
        _front       = other._front;
        _capacity    = other._capacity;
        other._items = nullptr;
    }

    void enqueue(const T& packet)
    {

#ifdef DEBUG_BUILD
        if (_num_items >= _max_size)
            throw std::logic_error("Attempted to enqueue a full FixedQueue");
#endif

        size_t rear  = (_front + _num_items) % _capacity;
        _items[rear] = packet;
        _num_items++;
    }

    T dequeue()
    {

#ifdef DEBUG_BUILD
        if (_num_items == 0)
            throw std::logic_error("Attempted to dequeue an empty FixedQueue");
#endif

        T res  = _items[_front];
        _front = (_front + 1) % _capacity;
        _num_items--;
        return res;
    }

    size_t size() const { return _num_items; }
    size_t max_size() const { return _max_size; }

  private:
    T*     _items;
    size_t _max_size;

    size_t _num_items = 0;

    size_t _front = 0;
    size_t _capacity;
};
