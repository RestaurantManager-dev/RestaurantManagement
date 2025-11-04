#include <iostream>
#include "DataStructures/LinkedList.hpp"

int main(int, char **)
{
    LinkedList<int> list;
    list.enqueue(10);
    list.enqueue(20);
    list.enqueue(30);
    std::cout << "Front element is: " << list.peek() << std::endl;
    list.dequeue();
    std::cout << "Front element after dequeue is: " << list.peek() << std::endl;
    list.remove(20);
    std::cout << "Front element after removing 20 is: " << list.peek() << std::endl;

    return 0;
}
