#include "RestaurantLogic/Cook/VeganCook.hpp"

VeganCook::VeganCook(int ID, int speed, int breakDuration,
                     int ordersBeforeBreak)
    : Cook(ID, speed, breakDuration, ordersBeforeBreak)
{
}

CookType VeganCook::getType() const
{
    return CookType::Vegan;
}