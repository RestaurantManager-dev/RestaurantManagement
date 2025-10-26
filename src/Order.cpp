#include "Order.hpp"

Order::Order(const TimeStep &arrivalTime, int size, double price) : arrivalTime(arrivalTime), size(size), price(price)
{
}
TimeStep Order::getArrivalTime() const
{
    return arrivalTime;
}
int Order::getSize() const
{
    return size;
}
double Order::getPrice() const
{
    return price;
}