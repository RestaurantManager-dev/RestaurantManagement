#pragma once

#include "DataStructures/LinkedList.hpp"

// Node implementation
template <typename T>
Node<T>::Node() : key(-1), data(T()), next(nullptr)
{
}

template <typename T>
Node<T>::Node(T d) : key(-1), data(d), next(nullptr)
{
}

template <typename T>
Node<T>::~Node()
{
}

template <typename T>
void Node<T>::setData(T d)
{
    data = d;
}

template <typename T>
void Node<T>::setNext(Node *n)
{
    next = n;
}

template <typename T>
void Node<T>::setKey(int k)
{
    key = k;
}

template <typename T>
T Node<T>::getData() const
{
    return data;
}

template <typename T>
Node<T> *Node<T>::getNext() const
{
    return next;
}

template <typename T>
int Node<T>::getKey() const
{
    return key;
}

// LinkedList implementation
template <typename T>
LinkedList<T>::LinkedList()
{
}

template <typename T>
LinkedList<T>::~LinkedList()
{
}
