#include "DataStructures/Queue.hpp"
#include "Queue.hpp"

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
    while (!isEmpty())
    {
        dequeue();
    }
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
int Queue<T>::getSize() const
{
    return size;
}

template <typename T>
void Queue<T>::enqueue(const T &data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (isEmpty())
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
    if (isEmpty())
    {
        return false;
    }

    Node *temp = head->next;
    delete head;
    head = temp;

    size--;

    if (isEmpty())
    {
        tail = nullptr;
    }

    return true;
}

template <typename T>
T Queue<T>::peek() const
{
    return head->data;
}
