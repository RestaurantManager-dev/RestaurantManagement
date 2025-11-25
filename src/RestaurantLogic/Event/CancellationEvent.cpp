#include "RestaurantLogic/Event/CancellationEvent.hpp"

CancellationEvent::CancellationEvent(int timeStep) : Event(timeStep) {}

EventType CancellationEvent::getType() const
{
    return EventType::Cancellation;
}

void CancellationEvent::setOrderId(int id)
{
    orderId = id;
}

int CancellationEvent::getOrderId() const
{
    return orderId;
}