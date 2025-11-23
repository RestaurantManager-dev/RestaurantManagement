#include "RestaurantLogic/Event/PromotionEvent.hpp"

PromotionEvent::PromotionEvent(int timeStep)
    : Event(timeStep)
{
}

EventType PromotionEvent::getType() const
{
    return EventType::Promotion;
}
