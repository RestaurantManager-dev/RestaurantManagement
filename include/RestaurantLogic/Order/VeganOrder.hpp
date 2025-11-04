#pragma once

#include "RestaurantLogic/Order/Order.hpp"

class VeganOrder : public Order
{
public:
    VeganOrder(int ID, int arrivalTime, int size, double price);
    ~VeganOrder() = default;
    virtual OrderType getType() const override;
};