#include "DataStructures/Queue.hpp"
#include <stdexcept>

template <typename T>
class Queue<T>::Node
{
public:
    T data;
    Node *next;
};

template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr), size(0)
{
}

template <typename T>
Queue<T>::~Queue()
{
    while(!isEmpty())
    {
        dequeue();
    }
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
void Queue<T>::enqueue(const T &data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if(isEmpty())
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T>
bool Queue<T>::dequeue()
{
    if(isEmpty())
    {
        throw std::out_of_range(
            "Error: Attempt to dequeue from an empty linked list.");
        return false;
    }

    Node *temp = head->next;
    delete head;
    head = temp;

    size--;

    if(isEmpty())
    {
        tail = nullptr;
    }

    return true;
}

template <typename T>
T Queue<T>::remove(const T &data)
{
    Node *current = head;
    Node *prev = nullptr;

    while(current)
    {
        if(current->data == data)
        {
            if(current == head)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            if(current == tail)
            {
                tail = prev;
            }
            T value = current->data;
            delete current;
            size--;
            return value;
        }
        prev = current;
        current = current->next;
    }
    throw std::invalid_argument(
        "Error: Attempt to remove non-existent element from linked list.");
}

template <typename T>
T Queue<T>::peek() const
{
    if(isEmpty())
    {
        throw std::out_of_range(
            "Error: Attempt to peek from an empty linked list.");
    }
    return head->data;
}
