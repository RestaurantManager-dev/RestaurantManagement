#pragma once

#include "DataStructures/DataStructures.hpp"
#include "RestaurantLogic/Cook/Cooks.hpp"
#include "RestaurantLogic/Event/Events.hpp"
#include "RestaurantLogic/Order/Orders.hpp"

class Restaurant
{
private:
    HashMap<Order *> orderMap;

    Queue<Order *> waitingNormalOrders;
    Queue<Order *> waitingVeganOrders;
    PriorityQueue<Order *, VIPOrder::Comparator> waitingVIPOrders;

    Queue<Order *> inServiceNormalOrders;
    Queue<Order *> inServiceVeganOrders;
    Queue<Order *> inServiceVIPOrders;

    Queue<Order *> finishedOrders;

    HashMap<Cook *> cookMap;

    Queue<Cook *> availableNormalCooks;
    Queue<Cook *> availableVeganCooks;
    Queue<Cook *> availableVIPCooks;

    Queue<Cook *> onBreakNormalCooks;
    Queue<Cook *> onBreakVeganCooks;
    Queue<Cook *> onBreakVIPCooks;

    

public:
    Restaurant();
    ~Restaurant() = default;
    void simulate();
};
