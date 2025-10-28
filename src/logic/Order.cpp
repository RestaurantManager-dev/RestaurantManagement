#include "Order.hpp"

Order::Order(int ID, int arrivalTime, int size, double price) : ID(ID), arrivalTime(arrivalTime), size(size), price(price)
{
    progress = OrderProgress::Waiting;
    assignedTime = -1;
    finishTime = -1;
}
int Order::getID() const
{
    return ID;
}
int Order::getArrivalTime() const
{
    return arrivalTime;
}
int Order::getAssignedTime() const
{
    return assignedTime;
}
int Order::getFinishTime() const
{
    return finishTime;
}
int Order::getWaitingTime() const
{
    return assignedTime - arrivalTime;
}
int Order::getServiceTime() const
{
    return finishTime - assignedTime;
}
int Order::getSize() const
{
    return size;
}
double Order::getPrice() const
{
    return price;
}

OrderProgress Order::getProgress() const
{
    return progress;
}

void Order::setAssignedTime(int assignedTime)
{
    this->assignedTime = assignedTime;
}

void Order::setFinishTime(int finishTime)
{
    this->finishTime = finishTime;
}

void Order::setPrice(double price)
{
    this->price = price;
}

void Order::setProgress(OrderProgress progress)
{
    this->progress = progress;
}
