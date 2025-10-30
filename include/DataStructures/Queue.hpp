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

    bool isEmpty() const;
    int getSize() const;

    void enqueue(const T &data);
    bool dequeue();

    T peek() const;
};

#include "DataStructures/Queue.tpp"
