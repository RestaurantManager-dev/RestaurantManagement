#pragma once

#include "Order.hpp"

class NormalOrder: public Order
{
public:
    NormalOrder(int ID, int arrivalTime, int size, double price);
    ~NormalOrder() = default;
    virtual OrderType getType() const override;
};


