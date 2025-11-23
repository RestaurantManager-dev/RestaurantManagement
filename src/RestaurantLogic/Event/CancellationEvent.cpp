#include "RestaurantLogic/Event/CancellationEvent.hpp"

CancellationEvent::CancellationEvent(int timeStep)
    : Event(timeStep)
{
}

EventType CancellationEvent::getType() const
{
    return EventType::Cancellation;
}
