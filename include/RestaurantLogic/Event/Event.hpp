#pragma once

#include "DataStructures/Queue.hpp"
#include "RestaurantLogic/Order/Order.hpp"

enum class EventType
{
    Arrival,
    Cancellation,
    Promotion
};

class Event : public QueueNode<Event *>
{
private:
    int timeStep;

public:
    Event(int timeStep);
    virtual ~Event() = default;
    int getTimeStep() const;
    void setTimeStep(int timeStep);
    virtual EventType getType() const = 0;
};
