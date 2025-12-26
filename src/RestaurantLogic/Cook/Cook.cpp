#include "RestaurantLogic/Cook/Cook.hpp"

Cook::Cook(int ID, int speed, int breakDuration, int ordersBeforeBreak)
    : ID(ID), speed(speed), breakDuration(breakDuration),
      ordersBeforeBreak(ordersBeforeBreak)
{
    status = CookStatus::Available;
    ordersServed = 0;
    currentOrderID = -1;
    assignedTime = -1;
    breakStartTime = -1;
    basespeed = speed;
    fatigue = .9;
    injuryduration = 10;
    injuryprop = .1;

   // breakStartTime = 0;
}

int Cook::getID() const
{
    return ID;
}

double Cook::getSpeed() const
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

int Cook::getEndTimeOfCurrentOrder() const
{
    return endTimeOfCurrentOrder;
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

bool Cook::serveOrder(int stime)
{
    ordersServed++;
    if(ordersServed >= ordersBeforeBreak)
    {
        setStatus(CookStatus::OnBreak);
        setOrdersServed(0);
        setBreakStartTime(stime);
        speed = basespeed;
        return false;
    }
    
    setStatus(CookStatus::Available);
    setCurrentOrderID(-1);
    setAssignedTime(-1);
    setCurrentOrderSize(-1);
    endTimeOfCurrentOrder = INFINITY;
    speed *= fatigue;

    // Injury
    srand(time(0));
    int num = rand() % 100;
    if(num <= injuryprop * 100)
    {
        setStatus(CookStatus::Injured);
        setOrdersServed(0);
        setBreakStartTime(stime);
        speed = basespeed;
        return false;
    }

    return true;
}

int Cook::getCurrentOrderSize() const
{
    return currentOrderSize;
}

void Cook::setCurrentOrderSize(int size)
{
    this->currentOrderSize = size;
}

void Cook::assignorder(Order *order, int timestep) {
    setCurrentOrderID(order->getID());
    setAssignedTime(timestep);
    setStatus(CookStatus::Busy);
    setCurrentOrderSize(order->getSize());

    order->setAssignedTime(timestep);
    order->setStatus(OrderStatus::InService);

    endTimeOfCurrentOrder = timestep + (order->getSize() / speed);
}

bool Cook::finishedbreak(int timestep) {
    int fts = getBreakStartTime() + getBreakDuration();
    
    if(fts <= timestep)
    {
        setStatus(CookStatus::Available);
        return true;
    }
    return false;
}

bool Cook::finishedinjury(int timestep)
{
    int fts = getBreakStartTime() + injuryduration;

    if(fts <= timestep)
    {
        setStatus(CookStatus::Available);
        return true;
    }
    return false;
}

void Cook::increasefatigue() {
    fatigue = fatigue - .1;
}