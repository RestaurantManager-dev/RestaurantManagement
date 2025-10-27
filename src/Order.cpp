#include "Order.hpp"

Order::Order(int arrivalTime, int size, double price) : arrivalTime(arrivalTime), size(size), price(price)
{
}
int Order::getArrivalTime() const
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