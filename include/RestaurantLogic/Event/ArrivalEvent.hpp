#pragma once

#include "RestaurantLogic/Event/Event.hpp"


class ArrivalEvent : public Event
{
public:
    ArrivalEvent(int timeStep);
    ~ArrivalEvent() = default;
    EventType getType() const override;

    void setOrderDetails(OrderType type, int id, int size, double total);
    
    OrderType getOrderType() const;
    int getorderid() const;
    int getordersize() const;
    int getordertotal() const;

private:
    OrderType orderType;
    int orderid;
    int ordersize;
    double ordertotal;
};
