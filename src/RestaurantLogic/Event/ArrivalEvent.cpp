#include "RestaurantLogic/Event/ArrivalEvent.hpp"

ArrivalEvent::ArrivalEvent(int timeStep) : Event(timeStep)
{
}

EventType ArrivalEvent::getType() const
{
    return EventType::Arrival;
}
