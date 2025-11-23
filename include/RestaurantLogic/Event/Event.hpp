#pragma once

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
    virtual EventType getType() const = 0;
};
