#pragma once

#include "RestaurantLogic/Event/Event.hpp"

class ArrivalEvent : public Event
{
public:
    ArrivalEvent(int timeStep);
    ~ArrivalEvent() = default;
    EventType getType() const override;
};
