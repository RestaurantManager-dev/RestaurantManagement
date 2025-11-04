#include <iostream>
#include <stdexcept>
#include "DataStructures/LinkedList.hpp"

int main(int, char **)
{
    try
    {

        LinkedList<int> list;
        list.enqueue(10);
        list.enqueue(20);
        list.enqueue(30);
        std::cout << "Front element is: " << list.peek() << std::endl;
        list.dequeue();
        std::cout << "Front element after dequeue is: " << list.peek() << std::endl;
        list.remove(20);
        list.remove(20);
        std::cout << "Front element after removing 20 is: " << list.peek() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "--------------------------" << std::endl;
        std::cerr << "CAUGHT AN EXCEPTION:" << std::endl;
        std::cerr << "  " << e.what() << std::endl;
        std::cerr << "--------------------------" << std::endl;
    }
    return 0;
}
