#pragma once

#include "RestaurantLogic/Event/Event.hpp"

class CancellationEvent : public Event
{
public:
    CancellationEvent(int timeStep);
    ~CancellationEvent() = default;
    EventType getType() const override;
    void GetData(std::string data) override;
};
