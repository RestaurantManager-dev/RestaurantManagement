#pragma once

template <typename Derived>
class QueueNode
{
    template <typename T>
    friend class Queue;

private:
    Derived prev = nullptr;
    Derived next = nullptr;
    bool inQueue = false;

public:
    QueueNode() = default;
    virtual ~QueueNode() = default;

    QueueNode(const QueueNode &) = delete;
    QueueNode &operator=(const QueueNode &) = delete;

    bool isInQueue() const
    {
        return inQueue;
    }
};

template <typename T>
class Queue
{
private:
    T head;
    T tail;
    int size;

public:
    Queue();
    ~Queue();

    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    int getSize() const;
    bool isEmpty() const;

    void enqueue(T item);
    T dequeue();
    void remove(T item);
    T peek() const;
    void clear();
};

#include "DataStructures/Queue.tpp"
