#include "LinkedList.hpp"

template <typename T>
class LinkedList<T>::Node
{
public:
    T data;
    Node *next;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0)
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

template <typename T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void LinkedList<T>::enqueue(const T &data)
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
bool LinkedList<T>::dequeue()
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
T LinkedList<T>::remove(const T &data)
{
    Node *current = head;
    Node *prev = nullptr;

    while (current)
    {
        if (current->data == data)
        {
            if (current == head)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            if (current == tail)
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
}

template <typename T>
T LinkedList<T>::peek() const
{
    return head->data;
}
