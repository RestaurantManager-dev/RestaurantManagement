#include "RestaurantLogic/Event/Event.hpp"

Event::Event(int timeStep) : timeStep(timeStep) {}

int Event::getTimeStep() const
{
    return timeStep;
}

void Event::setTimeStep(int timeStep)
{
    this->timeStep = timeStep;
}