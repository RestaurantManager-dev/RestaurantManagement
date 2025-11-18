#pragma once

template <typename T>
class Array
{
private:
    T *data;
    int capacity;
    int size;

    void resize();

public:
    Array(int initialCapacity = 10);
    ~Array();

    Array(const Array &) = delete;
    Array &operator=(const Array &) = delete;

    void push(T item);
    T pop();
    T &operator[](int index);
    const T &operator[](int index) const;
    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;
    void clear();
};

#include "DataStructures/Array.tpp"
