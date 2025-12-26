#pragma once

#include "RestaurantLogic/Order/Order.hpp"

class NormalOrder : public Order
{
public:
    NormalOrder(int ID, int arrivalTime, int size, double price);
    ~NormalOrder() = default;
    virtual OrderType getType() const override;

    class NormalComparator : public PriorityComparator<NormalOrder *>
    {
    public:
        bool operator()(NormalOrder *a, NormalOrder *b) const override
        {
            return a->getSize() < b->getSize();
        }
    };
};
