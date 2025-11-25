#include "RestaurantLogic/Event/PromotionEvent.hpp"

PromotionEvent::PromotionEvent(int timeStep)
    : Event(timeStep)
{
}

EventType PromotionEvent::getType() const
{
    return EventType::Promotion;
}

void PromotionEvent::setOrderID(int id) { orderid = id; }

void PromotionEvent::setExtraMoney(double money) { extraMoney = money; }

int PromotionEvent::getOrderID() const { return orderid; }

int PromotionEvent::getExtraMoney() const { return extraMoney; }