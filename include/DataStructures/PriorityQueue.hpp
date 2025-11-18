#pragma once

#include "DataStructures/Array.hpp"

template <typename T>
class PriorityComparator
{
public:
    virtual ~PriorityComparator() = default;
    // Return true if 'a' has higher priority than 'b'
    virtual bool operator()(T a, T b) const = 0;
};

template <typename T, typename Comparator>
class PriorityQueue
{
private:
    Array<T> heap;
    Comparator compare;

    int parent(int i);
    int leftChild(int i);
    int rightChild(int i);
    void swap(int i, int j);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    PriorityQueue(Comparator comp = Comparator());
    ~PriorityQueue() = default;

    PriorityQueue(const PriorityQueue &) = delete;
    PriorityQueue &operator=(const PriorityQueue &) = delete;

    void insert(T item);
    T extract();
    T peek() const;
    bool isEmpty() const;
    int getSize() const;
    void clear();
};

#include "DataStructures/PriorityQueue.tpp"
