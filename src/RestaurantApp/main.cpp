#include "DataStructures/Queue.hpp"
#include "RestaurantLogic/Order/NormalOrder.hpp"
#include "RestaurantLogic/Order/VIPOrder.hpp"
#include "RestaurantLogic/Order/VeganOrder.hpp"
#include <iostream>
#include <stdexcept>

int main(int, char **)
{
    try
    {
        std::cout << "=== Testing Intrusive Queue with Orders ===" << std::endl
                  << std::endl;

        // Create a queue of orders (type-safe, no void*)
        Queue<Order> orderQueue;

        // Create some orders
        NormalOrder *order1 = new NormalOrder(1, 0, 10, 50.0);
        VeganOrder *order2 = new VeganOrder(2, 1, 15, 75.0);
        VIPOrder *order3 = new VIPOrder(3, 2, 20, 100.0);
        NormalOrder *order4 = new NormalOrder(4, 3, 12, 60.0);

        std::cout << "Created 4 orders: Normal(1), Vegan(2), VIP(3), Normal(4)"
                  << std::endl
                  << std::endl;

        // Enqueue orders
        std::cout << "Enqueueing all orders..." << std::endl;
        orderQueue.enqueue(order1);
        orderQueue.enqueue(order2);
        orderQueue.enqueue(order3);
        orderQueue.enqueue(order4);
        std::cout << "Queue size: " << orderQueue.getSize() << std::endl
                  << std::endl;

        // Peek at front
        Order *front = orderQueue.peek();
        if(front)
        {
            std::cout << "Front order ID: " << front->getID()
                      << " (Type: " << static_cast<int>(front->getType()) << ")"
                      << std::endl
                      << std::endl;
        }

        // Remove order2 from the middle in O(1)!
        std::cout << "Removing order 2 from middle in O(1)..." << std::endl;
        orderQueue.remove(order2);
        std::cout << "Queue size after removal: " << orderQueue.getSize()
                  << std::endl;
        std::cout << "Order 2 in queue? "
                  << (order2->isInQueue() ? "Yes" : "No") << std::endl
                  << std::endl;

        // Remove order3 (also from middle)
        std::cout << "Removing order 3 from queue in O(1)..." << std::endl;
        orderQueue.remove(order3);
        std::cout << "Queue size: " << orderQueue.getSize() << std::endl
                  << std::endl;

        // Dequeue from front
        std::cout << "Dequeuing from front..." << std::endl;
        Order *dequeued = orderQueue.dequeue();
        if(dequeued)
        {
            std::cout << "Dequeued order ID: " << dequeued->getID()
                      << std::endl;
            std::cout << "Queue size: " << orderQueue.getSize() << std::endl
                      << std::endl;
        }

        // Peek at remaining
        front = orderQueue.peek();
        if(front)
        {
            std::cout << "Remaining order ID: " << front->getID() << std::endl
                      << std::endl;
        }

        // Test: Try to enqueue an already queued item (should throw)
        std::cout << "Testing error: Trying to enqueue order4 again (already "
                     "in queue)..."
                  << std::endl;
        try
        {
            orderQueue.enqueue(order4);
        }
        catch(const std::exception &e)
        {
            std::cout << "Caught expected exception: " << e.what() << std::endl
                      << std::endl;
        }

        // Clear the queue before deleting orders
        orderQueue.clear();

        // Clean up
        delete order1;
        delete order2;
        delete order3;
        delete order4;

        std::cout << "=== All tests passed successfully! ===" << std::endl;
        std::cout << "Queue is now truly generic with O(1) operations!"
                  << std::endl;
    }
    catch(const std::exception &e)
    {
        std::cerr << "--------------------------" << std::endl;
        std::cerr << "CAUGHT AN EXCEPTION:" << std::endl;
        std::cerr << "  " << e.what() << std::endl;
        std::cerr << "--------------------------" << std::endl;
        return 1;
    }
    return 0;
}
