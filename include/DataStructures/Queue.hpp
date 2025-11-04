#pragma once

#include "DataStructures/LinkedList.hpp"

template <typename T>
class Queue
{
private:
    LinkedList<T> list;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    int getSize() const;

    void enqueue(const T &data);
    bool dequeue();

    T peek() const;
};

#include "DataStructures/Queue.tpp"
