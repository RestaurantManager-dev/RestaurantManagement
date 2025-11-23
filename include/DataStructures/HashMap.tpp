#pragma once

#include "DataStructures/HashMap.hpp"

template <typename T>
HashMap<T>::HashMap(long long maxSize) : maxSize(maxSize)
{
    arr = new Node<T> *[maxSize];
    for(long long i = 0; i < maxSize; i++)
    {
        arr[i] = nullptr;
    }
}

template <typename T>
HashMap<T>::~HashMap()
{
    for(long long i = 0; i < maxSize; i++)
    {
        Node<T> *current = arr[i];
        while(current)
        {
            Node<T> *next = current->getNext();
            delete current;
            current = next;
        }
    }
    delete[] arr;
    arr = nullptr;
}

template <typename T>
void HashMap<T>::add(int key, T value)
{
    long long index = hash(key);
    Node<T> *temp = arr[index];
    if(temp)
    {
        if(temp->getKey() == key)
        {
            temp->setData(value);
            return;
        }
        while(temp->getNext())
        {
            if(temp->getKey() == key)
            {
                temp->setData(value);
                return;
            }
            temp = temp->getNext();
        }
        if(temp->getKey() == key)
        {
            temp->setData(value);
            return;
        }
        Node<T> *newNode = new Node<T>(value);
        newNode->setKey(key);
        temp->setNext(newNode);
    }
    else
    {
        Node<T> *newNode = new Node<T>(value);
        newNode->setKey(key);
        arr[index] = newNode;
    }
}

template <typename T>
T HashMap<T>::get(int key) const
{
    long long index = hash(key);
    Node<T> *temp = arr[index];
    while(temp)
    {
        if(temp->getKey() == key)
        {
            return temp->getData();
        }
        temp = temp->getNext();
    }
    return T();
}

template <typename T>
void HashMap<T>::remove(int key)
{
    long long index = hash(key);

    Node<T> *lastTemp = nullptr;
    Node<T> *temp = arr[index];
    while(temp)
    {
        if(temp->getKey() == key)
        {
            if(lastTemp)
            {
                lastTemp->setNext(temp->getNext());
                delete temp;
            }
            else
            {
                arr[index] = temp->getNext();
                delete temp;
            }
            return;
        }

        lastTemp = temp;
        temp = temp->getNext();
    }
}

template <typename T>
long long HashMap<T>::hash(int key) const
{
    return key % maxSize;
}
