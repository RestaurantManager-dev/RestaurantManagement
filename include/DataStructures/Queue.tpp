#include "DataStructures/Queue.hpp"
#include <stdexcept>

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), size(0)
{
}

template <typename T>
Queue<T>::~Queue()
{
    clear();
}

template <typename T>
int Queue<T>::getSize() const
{
    return size;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void Queue<T>::enqueue(T item)
{
    if(!item)
    {
        throw std::invalid_argument("Cannot enqueue null item");
    }
    // Allow Duplicats
    /* 
    if(item->inQueue)
    {
        throw std::invalid_argument("Item is already in a queue");
    }*/

    if(isEmpty())
    {
        QueueNode<T> *newNode = new QueueNode<T>;
        newNode->data = item;
        head = tail = newNode;
        newNode->inQueue = true;
    }
    else
    {
        QueueNode<T> *newNode = new QueueNode<T>;
        newNode->data = item;
        tail->next = newNode;
        newNode->prev = tail;

        tail = newNode;
        newNode->inQueue = true;
    }
    size++;
}

template <typename T>
QueueNode<T> *Queue<T>::dequeue()
{
    if(isEmpty())
    {
        return nullptr;
    }

    QueueNode<T> *item = head;
    remove(item);
    return item;
}

template <typename T>
void Queue<T>::remove(QueueNode<T> *item)
{
    if(!item)
    {
        return;
    }

    if(!item->inQueue)
    {
        // Nothing to do if it's not currently in this queue
        return;
    }

    // Update the previous node's next pointer
    if(item->prev)
    {
        item->prev->next = item->next;
    }
    else
    {
        // This was the head
        head = item->next;
    }

    // Update the next node's prev pointer
    if(item->next)
    {
        item->next->prev = item->prev;
    }
    else
    {
        // This was the tail
        tail = item->prev;
    }

    // Clear the item's pointers
    item->prev = item->next = nullptr;
    item->inQueue = false;
    size--;
}

template <typename T>
QueueNode<T> *Queue<T>::peek() const
{
    return head;
}

template <typename T>
void Queue<T>::clear()
{
    // Just clear the links, don't delete items (they're not owned by the queue)
    QueueNode<T> *current = head;
    while(current)
    {
        QueueNode<T> *next = current->next;
        current->prev = current->next = nullptr;
        current->inQueue = false;
        current = next;
    }

    head = tail = nullptr;
    size = 0;
}
