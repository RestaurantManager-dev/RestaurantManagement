#include "NormalOrder.hpp"

NormalOrder::NormalOrder(int ID, int arrivalTime, int size, double price) : Order(ID, arrivalTime, size, price)
{
}

OrderType NormalOrder::getType() const
{
    return Normal;
}