#pragma once

/**
 * @brief Base class for objects that can be stored in an intrusive Queue
 *
 * This uses CRTP (Curiously Recurring Template Pattern) for type safety.
 * Objects that want O(1) arbitrary removal should inherit from this class.
 *
 * Example: class Order : public QueueNode<Order> { ... };
 *
 * @tparam Derived The derived type that will be stored in the queue
 */
template <typename Derived>
class QueueNode
{
    template <typename T>
    friend class Queue;

private:
    Derived *prev = nullptr;
    Derived *next = nullptr;

public:
    QueueNode() = default;
    virtual ~QueueNode() = default;

    // Prevent copying to avoid breaking queue links
    QueueNode(const QueueNode &) = delete;
    QueueNode &operator=(const QueueNode &) = delete;

    /**
     * @brief Check if this node is currently in a queue
     * @return true if linked in a queue, false otherwise
     */
    bool isInQueue() const
    {
        return prev != nullptr || next != nullptr;
    }
};

/**
 * @brief Intrusive doubly-linked queue with O(1) operations
 *
 * This queue works with pointers to objects that inherit from QueueNode<T>.
 * It provides O(1) enqueue, dequeue, and arbitrary removal.
 *
 * @tparam T The type to store (must inherit from QueueNode<T>)
 */
template <typename T>
class Queue
{
private:
    T *head;
    T *tail;
    int size;

public:
    Queue();
    ~Queue();

    // Prevent copying
    Queue(const Queue &) = delete;
    Queue &operator=(const Queue &) = delete;

    int getSize() const;
    bool isEmpty() const;

    void enqueue(T *item);
    T *dequeue();
    void remove(T *item);
    T *peek() const;
    void clear();
};

#include "DataStructures/Queue.tpp"
