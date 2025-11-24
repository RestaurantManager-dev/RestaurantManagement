#pragma once

template <typename Derived>
class QueueNode
{
    template <typename T>
    friend class Queue;

private:
    // Shouldn't this be QueueNode<Derived> as well?
    // WHERE ON EARTH IS THE DATA TO BE STORED IN THE FIRST PLACE
    QueueNode<Derived> *prev = nullptr;
    QueueNode<Derived> *next = nullptr;
    Derived data;
    bool inQueue = false;

public:
    QueueNode() = default;
    virtual ~QueueNode() = default;

    QueueNode(Derived D) {
        data = D;
    }

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
    // Shouldn't this be QueueNode<T>?
    QueueNode<T> *head;
    QueueNode<T> *tail;
    int size;

public:
    Queue();
    ~Queue();

    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    int getSize() const;
    bool isEmpty() const;

    void enqueue(T item);
    QueueNode<T> *dequeue();
    void remove(QueueNode<T> *item);
    QueueNode<T> *peek() const;
    void clear();
};

#include "DataStructures/Queue.tpp"
