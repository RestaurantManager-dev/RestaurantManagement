#include "DataStructures/Queue.hpp"
#include <iostream>
#include <stdexcept>

int main(int, char **)
{
    try
    {

        Queue<int> queue;
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        std::cout << "Front element is: " << queue.peek() << std::endl;
        queue.dequeue();
        std::cout << "Front element after dequeue is: " << queue.peek()
                  << std::endl;
        queue.remove(20);
        queue.remove(20);
        std::cout << "Front element after removing 20 is: " << queue.peek()
                  << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << "--------------------------" << std::endl;
        std::cerr << "CAUGHT AN EXCEPTION:" << std::endl;
        std::cerr << "  " << e.what() << std::endl;
        std::cerr << "--------------------------" << std::endl;
    }
    return 0;
}
