#pragma once

#include "DataStructures/DataStructures.hpp"
#include "RestaurantLogic/Cook/Cooks.hpp"
#include "RestaurantLogic/Event/Events.hpp"
#include "RestaurantLogic/Event/Event.hpp"
#include "RestaurantLogic/Order/Orders.hpp"

#include "GUI/GUI.h"
#include "GUI/Defs.h"
#include "CMUgraphicsLib/auxil.h"

#include <string>
#include <fstream>
#include <iostream>

class Restaurant
{
private:
    int VIPOrdersOverloadThreshold;
    int NormalOrdersPromoteThreshold;
    int CurrentTimeStep;
    string msg;

    HashMap<Order *> orderMap;

    Queue<Order *> waitingNormalOrders;
    Queue<Order *> waitingVeganOrders;
    PriorityQueue<Order *, VIPOrder::Comparator> waitingVIPOrders;

    Queue<Order *> inServiceNormalOrders;
    Queue<Order *> inServiceVeganOrders;
    Queue<Order *> inServiceVIPOrders;

    Queue<Order *> finishedNormalOrders;
    Queue<Order *> finishedVeganOrders;
    Queue<Order *> finishedVIPOrders;

    HashMap<Cook *> cookMap;

    Queue<Cook *> availableNormalCooks;
    Queue<Cook *> availableVeganCooks;
    Queue<Cook *> availableVIPCooks;

    PriorityQueue<Cook *, Cook::FinishComparator> inServiceCooks;

    Queue<Cook *> onBreakNormalCooks;
    Queue<Cook *> onBreakVeganCooks;
    Queue<Cook *> onBreakVIPCooks;

    Queue<Cook *> injuredNormalCooks;
    Queue<Cook *> injuredVeganCooks;
    Queue<Cook *> injuredVIPCooks;

    Queue<Event *> eventsQueue;

    PROG_MODE mode;
    bool isfinished = false;
    GUI *gui;

    Array<int> order_ids;
    Array<int> cook_ids;

public:
    Restaurant();
    ~Restaurant();

    void simulate();
    bool isOverloaded() const;
    void loadFiles(std::string filePath);
    void writeOutput() const;
    void executeEvents();
    void ExecuteTimeStep();
    void Finish();
    void ShowStatusBar();
    void UpdateUI();
};
