#pragma once

#include "RestaurantLogic/Event/Event.hpp"

class PromotionEvent : public Event
{
public:
    PromotionEvent(int timeStep);
    ~PromotionEvent() = default;
    EventType getType() const override;

    void setOrderID(int id);
    void setExtraMoney(double money);

    int getOrderID() const;
    int getExtraMoney() const;

private:
    int orderid;
    double extraMoney;
};
