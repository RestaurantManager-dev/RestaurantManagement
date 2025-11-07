#include "RestaurantLogic/Order/VIPOrder.hpp"

VIPOrder::VIPOrder(int ID, int arrivalTime, int size, double price)
    : Order(ID, arrivalTime, size, price)
{
}

OrderType VIPOrder::getType() const
{
    return OrderType::VIP;
}
