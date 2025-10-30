#include "RestaurantLogic/Order/VeganOrder.hpp"

VeganOrder::VeganOrder(int ID, int arrivalTime, int size, double price) : Order(ID, arrivalTime, size, price)
{
}

OrderType VeganOrder::getType() const
{
    return OrderType::Vegan;
}
