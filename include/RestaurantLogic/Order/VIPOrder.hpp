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
    // you didn't include the order size nor the price
    class Comparator : public PriorityComparator<Order *>
    {
    public:
        bool operator()(Order *a, Order *b) const override
        {
            return a->getArrivalTime() < b->getArrivalTime();
        }
    };
};