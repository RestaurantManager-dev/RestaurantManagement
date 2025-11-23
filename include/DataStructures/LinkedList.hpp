#pragma once

template <typename T>
class Node
{
public:
    Node();
    Node(T d);
    ~Node();

    void setData(T d);
    void setNext(Node *n);
    void setKey(int k);

    T getData() const;
    Node *getNext() const;
    int getKey() const;

private:
    int key;
    T data;
    Node *next;
};

template <typename T>
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

private:
    Node<T> head;
};

#include "DataStructures/LinkedList.tpp"
