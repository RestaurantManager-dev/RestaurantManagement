#include "TimeStep.hpp"

TimeStep::TimeStep(int value) : value(value)
{
}

int TimeStep::getValue() const
{
    return value;
}