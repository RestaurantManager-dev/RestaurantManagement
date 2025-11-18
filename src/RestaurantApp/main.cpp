#include "DataStructures/PriorityQueue.hpp"
#include "RestaurantLogic/Order/VIPOrder.hpp"
#include <iostream>

int main()
{
    PriorityQueue<VIPOrder *, VIPOrder::Comparator> pq;
    // Create some VIP orders with different arrival times
    auto *o1 = new VIPOrder(101, 5, 2, 100.0); // arrives at 5
    auto *o2 = new VIPOrder(102, 1, 3, 200.0); // arrives at 1
    auto *o3 = new VIPOrder(103, 3, 1, 150.0); // arrives at 3

    pq.insert(o1);
    pq.insert(o2);
    pq.insert(o3);

    std::cout << "PQ size after inserts: " << pq.getSize() << "\n";

    // Peek should be the earliest arrival (ID 102, arrival 1)
    VIPOrder *top = pq.peek();
    if(top)
    {
        std::cout << "Peek -> ID: " << top->getID()
                  << ", arrival: " << top->getArrivalTime() << "\n";
    }

    // Extract in priority order
    std::cout << "Extraction order (by earliest arrival):\n";
    while(!pq.isEmpty())
    {
        VIPOrder *ord = pq.extract();
        if(ord)
        {
            std::cout << "ID: " << ord->getID()
                      << ", arrival: " << ord->getArrivalTime() << "\n";
            delete ord; // cleanup since PQ doesn't own items
        }
    }

    std::cout << "PQ empty? " << (pq.isEmpty() ? "yes" : "no") << "\n";
    return 0;
}