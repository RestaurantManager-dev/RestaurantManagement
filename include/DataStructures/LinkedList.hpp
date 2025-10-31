#pragma once

template <typename T>
class LinkedList
{
private:
    class Node;
    Node *head, *tail;
    int size;

public:
    LinkedList();
    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;

    void enqueue(const T &data);
    bool dequeue();

    T remove(const T &data);

    T peek() const;
};

#include "LinkedList.tpp"
