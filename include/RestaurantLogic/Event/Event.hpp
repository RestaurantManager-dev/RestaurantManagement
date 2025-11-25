#pragma once

#include "DataStructures/PriorityQueue.hpp"

enum class EventType
{
    Arrival,
    Cancellation,
    Promotion
};

class Event
{
private:
    int timeStep;

public:
    Event(int timeStep);
    virtual ~Event() = default;
    int getTimeStep() const;
    void setTimeStep(int timeStep);
    // void GetData ?? was in Mazen's branch
    virtual EventType getType() const = 0;

    class Comparator : public PriorityComparator<Event *>
    {
    public:
        bool operator()(Event *a, Event *b) const override
        {
            return a->getTimeStep() < b->getTimeStep();
        }
    };
};
