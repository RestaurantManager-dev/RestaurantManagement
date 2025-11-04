#pragma once

#include "RestaurantLogic/Order/Order.hpp"

class VIPOrder : public Order
{
public:
    VIPOrder(int ID, int arrivalTime, int size, double price);
    ~VIPOrder() = default;
    virtual OrderType getType() const override;
};