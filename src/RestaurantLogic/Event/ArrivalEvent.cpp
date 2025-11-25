#include "RestaurantLogic/Event/ArrivalEvent.hpp"

ArrivalEvent::ArrivalEvent(int timeStep) : Event(timeStep)
{
}

EventType ArrivalEvent::getType() const
{
    return EventType::Arrival;
}

void ArrivalEvent::setOrderDetails(OrderType type, int id, int size, double total)
{
    this->orderType = type;
    this->orderid = id;
    this->ordersize = size;
    this->ordertotal = total;
}

OrderType ArrivalEvent::getOrderType() const { return this->orderType; }

int ArrivalEvent::getorderid() const { return this->orderid; }

int ArrivalEvent::getordersize() const { return this->ordersize; }

int ArrivalEvent::getordertotal() const { return this->ordertotal; }