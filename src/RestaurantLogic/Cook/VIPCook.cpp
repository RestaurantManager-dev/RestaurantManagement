#include "RestaurantLogic/Cook/VIPCook.hpp"

VIPCook::VIPCook(int ID, int speed, int breakDuration, int ordersBeforeBreak) : Cook(ID, speed, breakDuration, ordersBeforeBreak)
{
}

CookType VIPCook::getType() const
{
    return CookType::VIP;
}