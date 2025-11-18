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
    class Comparator : public PriorityComparator<VIPOrder *>
    {
    public:
        bool operator()(VIPOrder *a, VIPOrder *b) const override
        {
            return a->getArrivalTime() < b->getArrivalTime();
        }
    };
};