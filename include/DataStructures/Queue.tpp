#include "DataStructures/Queue.hpp"
#include "Queue.hpp"

template <typename T>
Queue<T>::Queue()
{
}
template <typename T>
Queue<T>::~Queue()
{
}

template <typename T>
bool Queue<T>::isEmpty() const
{
    return list.isEmpty();
}

template <typename T>
int Queue<T>::getSize() const
{
    return list.getSize();
}

template <typename T>
void Queue<T>::enqueue(const T &data)
{
    return list.enqueue(data);
}

template <typename T>
bool Queue<T>::dequeue()
{
    return list.dequeue();
}

template <typename T>
T Queue<T>::peek() const
{
    return list.peek();
}
