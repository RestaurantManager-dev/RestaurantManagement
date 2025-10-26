#pragma once

#include "TimeStep.hpp"
#include <string>

class Order
{
private:
    TimeStep arrivalTime;
    int size;
    double price;

public:
    Order(const TimeStep &arrivalTime, int size, double price);
    virtual ~Order() = default;
    TimeStep getArrivalTime() const;
    int getSize() const;
    double getPrice() const;
    virtual std::string getType() const = 0;
};
