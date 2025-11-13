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
void Queue<T>::enqueue(T *item)
{
    if(!item)
    {
        throw std::invalid_argument("Cannot enqueue null item");
    }

    if(item->prev != nullptr || item->next != nullptr)
    {
        throw std::invalid_argument("Item is already in a queue");
    }

    if(isEmpty())
    {
        head = tail = item;
        item->prev = item->next = nullptr;
    }
    else
    {
        tail->next = item;
        item->prev = tail;
        item->next = nullptr;
        tail = item;
    }
    size++;
}

template <typename T>
T *Queue<T>::dequeue()
{
    if(isEmpty())
    {
        return nullptr;
    }

    T *item = head;
    remove(item);
    return item;
}

template <typename T>
void Queue<T>::remove(T *item)
{
    if(!item)
    {
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
    size--;
}

template <typename T>
T *Queue<T>::peek() const
{
    return head;
}

template <typename T>
void Queue<T>::clear()
{
    // Just clear the links, don't delete items (they're not owned by the queue)
    T *current = head;
    while(current)
    {
        T *next = current->next;
        current->prev = current->next = nullptr;
        current = next;
    }

    head = tail = nullptr;
    size = 0;
}
