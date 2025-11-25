#pragma once

#include "RestaurantLogic/Event/Event.hpp"

class CancellationEvent : public Event
{
public:
    CancellationEvent(int timeStep);
    ~CancellationEvent() = default;
    EventType getType() const override;
    
    void setOrderId(int id);
    int getOrderId() const;

private:
    int orderId;
};
