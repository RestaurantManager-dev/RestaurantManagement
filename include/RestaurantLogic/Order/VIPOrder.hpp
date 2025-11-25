#pragma once

#include "DataStructures/PriorityQueue.hpp" // for PriorityComparator
#include "RestaurantLogic/Order/Order.hpp"

class VIPOrder : public Order
{
public:
    VIPOrder(int ID, int arrivalTime, int size, double price);
    ~VIPOrder() = default;
    virtual OrderType getType() const override;

    // Nested comparator: earlier arrival time = higher priority
    class Comparator : public PriorityComparator<Order *>
    {
    public:
        bool operator()(Order *a, Order *b) const override
        {
            int scorea = -a->getArrivalTime() + a->getSize() + a->getPrice();
            int scoreb = -b->getArrivalTime() + b->getSize() + b->getPrice(); 
            return scorea > scoreb;
        }
    };
};