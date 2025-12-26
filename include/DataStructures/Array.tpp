#include "DataStructures/Array.hpp"
#include <stdexcept>

template <typename T>
Array<T>::Array(int initialCapacity) : capacity(initialCapacity), size(0)
{
    data = new T[capacity];
}

template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

template <typename T>
void Array<T>::resize()
{
    capacity *= 2;
    T *newData = new T[capacity];
    for(int i = 0; i < size; i++)
    {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename T>
void Array<T>::push(T item)
{
    if(size == capacity)
    {
        resize();
    }
    data[size] = item;
    size++;
}

template <typename T>
T Array<T>::pop()
{
    if(size == 0)
    {
        throw std::out_of_range("Cannot pop from empty array");
    }
    size--;
    return data[size];
}

template <typename T>
T &Array<T>::operator[](int index)
{
    if(index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
const T &Array<T>::operator[](int index) const
{
    if(index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

template <typename T>
int Array<T>::getSize() const
{
    return size;
}

template <typename T>
int Array<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
bool Array<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
void Array<T>::clear()
{
    size = 0;
}


template <typename T>
void Array<T>::remove(T sdata)
{
    bool found = false;
    for(int i = 0; i < size; i++)
    {
        if(data[i] == sdata) { found = true; continue;}
        if(found)
        {
            data[i - 1] = data[i];
        }
    }
    if(found)
        size--;
}