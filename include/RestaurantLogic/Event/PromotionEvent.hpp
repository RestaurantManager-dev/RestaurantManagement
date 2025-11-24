#pragma once

#include "RestaurantLogic/Event/Event.hpp"

class PromotionEvent : public Event
{
public:
    PromotionEvent(int timeStep);
    ~PromotionEvent() = default;
    EventType getType() const override;
    void GetData(std::string data) override;
};
