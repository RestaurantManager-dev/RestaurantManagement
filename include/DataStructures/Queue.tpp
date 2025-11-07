#include "DataStructures/Queue.hpp"
#include <stdexcept>

template <typename T>
class Queue<T>::Node
{
public:
    T data;
    Node *next;
    Node *prev;
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
void *Queue<T>::enqueue(const T &data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = tail;

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
    return (void *)newNode;
}

template <typename T>
void Queue<T>::dequeue()
{
    if(isEmpty())
    {
        throw std::out_of_range(
            "Error: Attempt to dequeue from an empty linked list.");
    }

    Node *temp = head;
    head = head->next;

    if(head)
    {
        head->prev = nullptr;
    }
    else
    {
        tail = nullptr;
    }

    delete temp;
    size--;
}

template <typename T>
T Queue<T>::remove(const T &data)
{
    Node *current = head;
    while(current)
    {
        if(current->data == data)
        {
            return removeNode((void *)current);
        }
        current = current->next;
    }
    throw std::invalid_argument(
        "Error: Attempt to remove non-existent element from linked list.");
}

template <typename T>
T Queue<T>::removeNode(void *node)
{
    if(!node)
    {
        throw std::invalid_argument("Error: Attempt to remove a null node.");
    }

    Node *nodeToRemove = static_cast<Node *>(node);
    T value = nodeToRemove->data;

    if(nodeToRemove->prev)
    {
        nodeToRemove->prev->next = nodeToRemove->next;
    }
    else
    {
        head = nodeToRemove->next;
    }

    if(nodeToRemove->next)
    {
        nodeToRemove->next->prev = nodeToRemove->prev;
    }
    else
    {
        tail = nodeToRemove->prev;
    }

    delete nodeToRemove;
    size--;
    return value;
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
