#pragma once

#include "Cook.hpp"

class VeganCook : public Cook
{
public:
    VeganCook(int ID, int speed, int breakDuration, int ordersBeforeBreak);
    ~VeganCook() = default;
    virtual CookType getType() const override;
};