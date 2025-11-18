#include "LinkedList.hpp"
#pragma once


template <typename T>
class HashMap
{
public:
    HashMap(long long maxsize) : max_size(maxsize) {
        arr = new Node<T>*[maxsize];
        for(int i = 0; i < maxsize; i++)
        {
            arr[i] = nullptr;
        }
    }
    ~HashMap() {
        delete arr;
        arr = nullptr;
    }

    void Add(int key, T value) {
        long long index = Hash(key);
        Node<T> *temp = arr[index];
        if (temp) {
            if(temp->getkey() == key)
            {
                temp->setdata(value);
                return;
            }
            while(temp->getnext())
            {
                if(temp->getkey() == key)
                {
                    temp->setdata(value);
                    return;
                }
                temp = temp->getnext();
            }
            Node<T> *new_node = new Node<T>(value);
            new_node->setkey(key);
            temp->setnext(new_node);
        }
        else
        {
            Node<T> *new_node = new Node<T>(value);
            new_node->setkey(key);
            arr[index] = new_node;
        }
    }

    T Get(int key) const {
        long long index = Hash(key);
        Node<T> *temp = arr[index];
        while(temp)
        {
            if(temp->getkey() == key)
            {
                return temp->getdata();
            }
            temp = temp->getnext();
        }
        return 0;
    }

    void Delete(int key) {
        long long index = Hash(key);

        Node<T> *lasttemp = nullptr;
        Node<T> *temp = arr[index];
        while(temp)
        {
            if(temp->getkey() == key)
            {
                if(lasttemp)
                {
                    lasttemp->setnext(temp->getnext());
                    delete temp;
                }
                else
                {
                    arr[index] = arr[index]->getnext();
                    delete temp;
                }
            }

            lasttemp = temp;
            temp = temp->getnext();
        }
    }


private:
    long long max_size;
    Node<T>** arr; // an array of pointers

    long long Hash(int key) const {
        return key % max_size;
    }

};
