#pragma once

#include "DataStructures/LinkedList.hpp"

template <typename T>
class HashMap
{
public:
    HashMap(long long maxSize);
    ~HashMap();

    void add(int key, T value);
    T get(int key) const;
    void remove(int key);

private:
    long long maxSize;
    Node<T> **arr;

    long long hash(int key) const;
};

#include "DataStructures/HashMap.tpp"
