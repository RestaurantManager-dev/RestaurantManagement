#include "Cook.hpp"

Cook::Cook(int ID, int speed, int breakDuration, int ordersBeforeBreak) : ID(ID), speed(speed), breakDuration(breakDuration), ordersBeforeBreak(ordersBeforeBreak)
{
    status = CookStatus::Available;
    ordersServed = 0;
    currentOrderID = -1;
    assignedTime = -1;
    breakStartTime = -1;
}

int Cook::getID() const
{
    return ID;
}

int Cook::getSpeed() const
{
    return speed;
}

CookStatus Cook::getStatus() const
{
    return status;
}

int Cook::getOrdersServed() const
{
    return ordersServed;
}

int Cook::getBreakDuration() const
{
    return breakDuration;
}

int Cook::getOrdersBeforeBreak() const
{
    return ordersBeforeBreak;
}

int Cook::getCurrentOrderID() const
{
    return currentOrderID;
}

int Cook::getAssignedTime() const
{
    return assignedTime;
}

int Cook::getBreakStartTime() const
{
    return breakStartTime;
}

void Cook::setStatus(CookStatus status)
{
    this->status = status;
}

void Cook::setOrdersServed(int count)
{
    this->ordersServed = count;
}

void Cook::setCurrentOrderID(int orderID)
{
    this->currentOrderID = orderID;
}

void Cook::setAssignedTime(int time)
{
    this->assignedTime = time;
}

void Cook::setBreakStartTime(int time)
{
    this->breakStartTime = time;
}

bool Cook::serveOrder()
{
    ordersServed++;
    if (ordersServed >= ordersBeforeBreak)
    {
        setStatus(CookStatus::OnBreak);
        setOrdersServed(0);
        return false;
    }
    return true;
}