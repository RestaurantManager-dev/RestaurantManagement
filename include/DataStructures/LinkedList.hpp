#pragma once


template <typename T>
class Node
{
public:
    Node() {
        next = nullptr;
    }


    Node(T d): data(d){
        next = nullptr;
        key = -1;
    }
    ~Node() {}

    void setdata(T d) { data = d; }
    void setnext(Node *n) { next = n; }
    void setkey(int k) { key = k; }

    T getdata() const { return data; }
    Node *getnext() const { return next; }
    int getkey() const { return key; }

private:
    int key;
    T data;
    Node *next;
};


template<typename T>
class LinkedList
{
public:
    LinkedList() {}

    ~LinkedList() {}

private:
    Node<T> Head;
};
