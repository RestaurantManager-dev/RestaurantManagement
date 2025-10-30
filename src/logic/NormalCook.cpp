#include "NormalCook.hpp"

NormalCook::NormalCook(int ID, int speed, int breakDuration, int ordersBeforeBreak) : Cook(ID, speed, breakDuration, ordersBeforeBreak)
{
}

CookType NormalCook::getType() const
{
    return CookType::Normal;
}