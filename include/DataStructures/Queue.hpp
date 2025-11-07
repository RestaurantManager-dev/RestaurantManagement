#pragma once

template <typename T>
class Queue
{
private:
    class Node;
    Node *head, *tail;
    int size;

public:
    Queue();
    ~Queue();

    int getSize() const;
    bool isEmpty() const;

    void* enqueue(const T &data);
    void dequeue();

    T remove(const T &data);
    T removeNode(void *node);

    T peek() const;
};

#include "DataStructures/Queue.tpp"
