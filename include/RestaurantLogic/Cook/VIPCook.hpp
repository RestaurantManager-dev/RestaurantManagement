#pragma once

#include "Cook.hpp"

class VIPCook : public Cook
{
public:
    VIPCook(int ID, int speed, int breakDuration, int ordersBeforeBreak);
    ~VIPCook() = default;
    virtual CookType getType() const override;
};