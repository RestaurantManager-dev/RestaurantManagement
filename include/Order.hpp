#pragma once

#include <string>

class Order
{
private:
    int arrivalTime;
    int size;
    double price;

public:
    Order(int arrivalTime, int size, double price);
    virtual ~Order() = default;
    int getArrivalTime() const;
    int getSize() const;
    double getPrice() const;
    virtual std::string getType() const = 0;
};
