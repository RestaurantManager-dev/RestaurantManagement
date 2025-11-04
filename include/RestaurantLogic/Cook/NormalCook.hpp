#pragma once

#include "RestaurantLogic/Cook/Cook.hpp"

class NormalCook : public Cook
{
public:
    NormalCook(int ID, int speed, int breakDuration, int ordersBeforeBreak);
    ~NormalCook() = default;
    virtual CookType getType() const override;
};