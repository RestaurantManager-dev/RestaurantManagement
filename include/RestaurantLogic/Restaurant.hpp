#pragma once

#include "DataStructures/DataStructures.hpp"
#include "RestaurantLogic/Cook/Cooks.hpp"
#include "RestaurantLogic/Event/Events.hpp"
#include "RestaurantLogic/Event/Event.hpp"
#include "RestaurantLogic/Order/Orders.hpp"

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Restaurant
{
private:
    int VIPOrdersOverloadThreshold;
    int NormalOrdersPromoteThreshold;
    int CurrentTimeStep;

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

    PriorityQueue<Cook *, Cook::FinishComparator> inServiceCooks;

    Queue<Cook *> onBreakNormalCooks;
    Queue<Cook *> onBreakVeganCooks;
    Queue<Cook *> onBreakVIPCooks;

    Queue<Event *> eventsQueue;

public:
    Restaurant();
    ~Restaurant() = default;

    void simulate();
    bool isOverloaded() const;
    void loadFiles(std::string filePath);
    void writeOutput() const;
    void executeEvents();
};
