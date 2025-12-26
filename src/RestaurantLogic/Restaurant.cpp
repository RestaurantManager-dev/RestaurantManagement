#include "RestaurantLogic/Restaurant.hpp"

Restaurant::Restaurant() : orderMap(10007), cookMap(10007)
{
    gui = new GUI();
    VIPOrdersOverloadThreshold = 5;
    // Will be changed from load file
    NormalOrdersPromoteThreshold = -1;
    CurrentTimeStep = 0;
    msg = "";
}

Restaurant::~Restaurant() {
    if(gui)
        delete gui;
    gui = nullptr;
}

bool Restaurant::isOverloaded() const
{
    return waitingVIPOrders.getSize() >= VIPOrdersOverloadThreshold;
}

void Restaurant::loadFiles(std::string filePath)
{
    /*
    * GET & STORE ALL THE EVENTS & COOKS
    */
    std::ifstream file(filePath);
    if(!file.is_open())
    {
        std::cout << "Can't open" << std::endl;
    }
    // std::cout << "File opened successfully" << std::endl;
    std::string line;

    // Number of cooks
    int N, G, V;
    int SN, SG, SV;
    int Bo;
    int BN, BG, BV;

    file >> N >> G >> V;
    file >> SN >> SG >> SV;
    file >> Bo >> BN >> BG >> BV;

    int id = 0;
    for(int i = 0; i < N; i++)
    {
        Cook *normalCook = new NormalCook(id, SN, BN, Bo);
        availableNormalCooks.enqueue(normalCook);
        cookMap.add(id, normalCook);
        cook_ids.push(id);
        id++;
    }
    for(int i = 0; i < G; i++)
    {
        Cook *veganCook = new VeganCook(id, SG, BG, Bo);
        availableVeganCooks.enqueue(veganCook);
        cookMap.add(id, veganCook);
        cook_ids.push(id);
        id++;
    }
    for(int i = 0; i < V; i++)
    {
        Cook *VipCook = new VIPCook(id, SV, BV, Bo);
        availableVIPCooks.enqueue(VipCook);
        cookMap.add(id, VipCook);
        cook_ids.push(id);
        id++;
    }

    file >> NormalOrdersPromoteThreshold;

    int m;
    file >> m;
    for(int i = 0; i < m; i++)
    {
        char evtype;
        file >> evtype;
        if(evtype == 'R')
        {
            char type;
            int artime, id, size, total;
            file >> type >> artime >> id >> size >> total;
            OrderType typenum;

            Event *event = new ArrivalEvent(artime);

            if(type == 'N')
            {
                typenum = OrderType::Normal;
            }
            else if(type == 'G')
            {
                typenum = OrderType::Vegan;
            }
            else if(type == 'V')
            {
                typenum = OrderType::VIP;
            }

            dynamic_cast<ArrivalEvent *>(event)->setOrderDetails(typenum, id,
                                                                 size, total);
            eventsQueue.enqueue(event);
        }
        else if(evtype == 'X')
        {
            int cantime, id;
            file >> cantime >> id;
            Event *event = new CancellationEvent(cantime);
            dynamic_cast<CancellationEvent *>(event)->setOrderId(id);

            eventsQueue.enqueue(event);
        }
        else if(evtype == 'P')
        {
            int protime, id, prototal;
            file >> protime >> id >> prototal;

            Event *event = new PromotionEvent(protime);
            dynamic_cast<PromotionEvent *>(event)->setOrderID(id);
            dynamic_cast<PromotionEvent *>(event)->setExtraMoney(prototal);

            eventsQueue.enqueue(event);
        }
    }

    file.close();
}

void Restaurant::writeOutput() const {
    // Make sure it only runs once
}

void Restaurant::executeEvents()
{
    /*
    * EXCUTE ALL EVENTS IN THIS TIME STEP [ARRIVAL + CANCELLATION + PROMOTION]
    */
    if(eventsQueue.isEmpty())
        return;

    Event *event = eventsQueue.peek();
    while(event && event->getTimeStep() <= this->CurrentTimeStep)
    {
        if(event->getType() == EventType::Arrival)
        {
            ArrivalEvent *Arevent = dynamic_cast<ArrivalEvent *>(event);
            if(Arevent->getOrderType() == OrderType::Normal)
            {
                Order *order = new NormalOrder(
                    Arevent->getorderid(), Arevent->getTimeStep(),
                    Arevent->getordersize(), Arevent->getordertotal());
                waitingNormalOrders.enqueue(order);
                orderMap.add(order->getID(), order);
                order_ids.push(order->getID());
            }
            else if(Arevent->getOrderType() == OrderType::Vegan)
            {
                Order *order = new VeganOrder(
                    Arevent->getorderid(), Arevent->getTimeStep(),
                    Arevent->getordersize(), Arevent->getordertotal());
                waitingVeganOrders.enqueue(order);
                orderMap.add(order->getID(), order);
                order_ids.push(order->getID());
            }
            else
            {
                Order *order = new VIPOrder(
                    Arevent->getorderid(), Arevent->getTimeStep(),
                    Arevent->getordersize(), Arevent->getordertotal());
                waitingVIPOrders.enqueue(order);
                orderMap.add(order->getID(), order);
                order_ids.push(order->getID());
            }
        }
        else if(event->getType() == EventType::Cancellation)
        {
            CancellationEvent *Cevent =
                dynamic_cast<CancellationEvent *>(event);
            int orderId = Cevent->getOrderId();
            Order *order = orderMap.get(orderId);
            if(order && order->getStatus() == OrderStatus::Waiting)
            {
                waitingNormalOrders.remove(order);
                orderMap.remove(orderId);
                order_ids.remove(order->getID());
                delete order;
            }
        }
        else if(event->getType() == EventType::Promotion)
        {
            PromotionEvent *Pevent = dynamic_cast<PromotionEvent *>(event);
            Order *porder = orderMap.get(Pevent->getOrderID());
            if(porder->getStatus() == OrderStatus::Waiting)
            {
                VIPOrder *new_porder =
                    new VIPOrder(porder->getID(), porder->getArrivalTime(),
                                 porder->getSize(),
                                 porder->getPrice() + Pevent->getExtraMoney());
                orderMap.add(porder->getID(), new_porder);
                waitingVIPOrders.enqueue(new_porder);
                
                if(porder->getType() == OrderType::Normal)
                {
                    waitingNormalOrders.remove(porder);
                }
                else
                {
                    waitingVeganOrders.remove(porder);
                }
                delete porder;
            }

        }

        eventsQueue.dequeue();
        event = eventsQueue.peek();
    }
}

void Restaurant::ExecuteTimeStep() {
    /*
    * Execute all events in this time step
    * Handle Assign cooks to orders
    * Handle finished orders
    * Handle rest cooks
    */
    msg = "";
    executeEvents();

    // Assigning orders
    Order *order = waitingVIPOrders.peek();
    while(order)
    {
        Cook *vipcook = availableVIPCooks.peek();
        Cook *normalcook = availableNormalCooks.peek();
        Cook *vegancook = availableVeganCooks.peek();
        if(vipcook)
        {
            vipcook->assignorder(order, CurrentTimeStep);
            availableVIPCooks.remove(vipcook);
            inServiceCooks.enqueue(vipcook);

            waitingVIPOrders.dequeue();
            inServiceVIPOrders.enqueue(order);

            msg += "vip cook#" + to_string(vipcook->getID())
                  + " is assigned VIP order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else if(normalcook)
        {
            normalcook->assignorder(order, CurrentTimeStep);
            availableNormalCooks.remove(normalcook);
            inServiceCooks.enqueue(normalcook);

            waitingVIPOrders.dequeue();
            inServiceVIPOrders.enqueue(order);

            msg += "normal cook#" + to_string(normalcook->getID())
                  + " is assigned VIP order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else if(vegancook)
        {
            vegancook->assignorder(order, CurrentTimeStep);
            availableVeganCooks.remove(vegancook);
            inServiceCooks.enqueue(vegancook);

            waitingVIPOrders.dequeue();
            inServiceVIPOrders.enqueue(order);

            msg += "vegan cook#" + to_string(vegancook->getID())
                  + " is assigned VIP order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else
        {
            break;
        }

        order = waitingVIPOrders.peek();
    }
    
    
    order = waitingVeganOrders.peek();
    while(order)
    {
        Cook *cook = availableVeganCooks.peek();
        if(cook)
        {
            cook->assignorder(order, CurrentTimeStep);
            availableVeganCooks.remove(cook);
            inServiceCooks.enqueue(cook);
            waitingVeganOrders.remove(order);
            inServiceVeganOrders.enqueue(order);

            msg += "vegan cook#" + to_string(cook->getID())
                  + " is assigned vegan order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else
        {
            break;
        }

        order = waitingVeganOrders.peek();
    
    }
    order = waitingNormalOrders.peek();
    while(order)
    {
        Cook *normalcook = availableNormalCooks.peek();
        Cook *VIPcook = availableVIPCooks.peek();
        if(normalcook)
        {
            normalcook->assignorder(order, CurrentTimeStep);
            
            availableNormalCooks.remove(normalcook);
            inServiceCooks.enqueue(normalcook);
            
            waitingNormalOrders.remove(order);
            inServiceNormalOrders.enqueue(order);

            msg += "normal cook#" + to_string(normalcook->getID())
                  + " is assigned Normal order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else if(VIPcook)
        {
            VIPcook->assignorder(order, CurrentTimeStep);
            
            availableVIPCooks.remove(VIPcook);
            inServiceCooks.enqueue(VIPcook);

            waitingNormalOrders.remove(order);
            inServiceNormalOrders.enqueue(order);

            msg += "VIP cook#" + to_string(VIPcook->getID())
                  + " is assigned Normal order #" + to_string(order->getID())
                  + " to prepare ";
        }
        else
        {
            break;
        }
        order = waitingNormalOrders.peek();
    }

    // Auto Promotion
    order = waitingNormalOrders.peek();
    while(order && (CurrentTimeStep - order->getArrivalTime()) >= NormalOrdersPromoteThreshold)
    {
        VIPOrder *new_order = new VIPOrder(
                order->getID(), order->getArrivalTime(), order->getSize(),
                order->getPrice());

        orderMap.add(order->getID(), new_order);
        waitingVIPOrders.enqueue(new_order);

        waitingNormalOrders.remove(order);
        delete order;
        order = waitingNormalOrders.peek();
    }


    // Check Finished Orders
    Cook *cook = inServiceCooks.peek();
    while(cook && cook->getEndTimeOfCurrentOrder() <= CurrentTimeStep)
    {
        int orderid = cook->getCurrentOrderID();
        Order *order = orderMap.get(orderid);
        msg += "Cook #" + to_string(cook->getID()) + "Finished Order #" + to_string(order->getID());
        
        inServiceCooks.dequeue();
        
        cook->serveOrder(CurrentTimeStep);
        if(cook->getStatus() == CookStatus::Available)
        {
            switch(cook->getType())
            {
            case CookType::Normal:
                availableNormalCooks.enqueue(cook);
                break;
            case CookType::Vegan:
                availableVeganCooks.enqueue(cook);
                break;
            case CookType::VIP:
                availableVIPCooks.enqueue(cook);
            }
        }
        else if(cook->getStatus() == CookStatus::OnBreak)
        {
            switch(cook->getType())
            {
            case CookType::Normal:
                onBreakNormalCooks.enqueue(cook);
                break;
            case CookType::Vegan:
                onBreakVeganCooks.enqueue(cook);
                break;
            case CookType::VIP:
                onBreakVIPCooks.enqueue(cook);
            }
            msg += "Cook #" + to_string(cook->getID()) + "is on rest";
        }
        else if(cook->getStatus() == CookStatus::Injured)
        {
            switch(cook->getType())
            {
            case CookType::Normal:
                injuredNormalCooks.enqueue(cook);
                break;
            case CookType::Vegan:
                injuredVeganCooks.enqueue(cook);
                break;
            case CookType::VIP:
                injuredVIPCooks.enqueue(cook);
            }
            msg += "Cook #" + to_string(cook->getID()) + "is injured";
        }

        
        order->setStatus(OrderStatus::Finished);
        order->setFinishTime(CurrentTimeStep);
        switch(order->getType())
        {
        case OrderType::VIP:
            inServiceVIPOrders.remove(order);
            finishedVIPOrders.enqueue(order);
            break;
        case OrderType::Normal:
            inServiceNormalOrders.remove(order);
            finishedNormalOrders.enqueue(order);
            break;
        case OrderType::Vegan:
            inServiceVeganOrders.remove(order);
            finishedVeganOrders.enqueue(order);
            break;
        }

        cook = inServiceCooks.peek();
    }


    // Get Cooks back from rest
    Cook *normal_cook = onBreakNormalCooks.peek();
    while(normal_cook && normal_cook->finishedbreak(CurrentTimeStep))
    {
        onBreakNormalCooks.dequeue();
        availableNormalCooks.enqueue(normal_cook);
        normal_cook = onBreakNormalCooks.peek();
    }

    Cook *vegan_cook = onBreakVeganCooks.peek();
    while(vegan_cook && vegan_cook->finishedbreak(CurrentTimeStep))
    {
        onBreakVeganCooks.dequeue();
        availableVeganCooks.enqueue(vegan_cook);
        vegan_cook = onBreakVeganCooks.peek();
    }

    Cook *vip_cook = onBreakVIPCooks.peek();
    while(vip_cook && vip_cook->finishedbreak(CurrentTimeStep))
    {
        onBreakVIPCooks.dequeue();
        availableVIPCooks.enqueue(vip_cook);
        vip_cook = onBreakVIPCooks.peek();
    }



    // Get Cooks back from injury
    normal_cook = injuredNormalCooks.peek();
    while(normal_cook && normal_cook->finishedinjury(CurrentTimeStep))
    {
        injuredNormalCooks.dequeue();
        availableNormalCooks.enqueue(normal_cook);
        normal_cook = injuredNormalCooks.peek();
    }

    vegan_cook = injuredVeganCooks.peek();
    while(vegan_cook && vegan_cook->finishedinjury(CurrentTimeStep))
    {
        injuredVeganCooks.dequeue();
        availableVeganCooks.enqueue(vegan_cook);
        vegan_cook = injuredVeganCooks.peek();
    }

    vip_cook = injuredVIPCooks.peek();
    while(vip_cook && vip_cook->finishedinjury(CurrentTimeStep))
    {
        injuredVIPCooks.dequeue();
        availableVIPCooks.enqueue(vip_cook);
        vip_cook = injuredVIPCooks.peek();
    }


    // Skip Breaks
    if(waitingVIPOrders.getSize() >= VIPOrdersOverloadThreshold)
    {
        Cook *vip_cook = onBreakVIPCooks.peek();
        if(vip_cook)
        {
            onBreakVIPCooks.dequeue();
            availableVIPCooks.enqueue(vip_cook);
            vip_cook->setStatus(CookStatus::Available);
            vip_cook->increasefatigue();
            msg += "Cook #" + to_string(vip_cook->getID()) + "Works over time";
        }

        Cook *normal_cook = onBreakNormalCooks.peek();
        if(normal_cook)
        {
            onBreakNormalCooks.dequeue();
            availableNormalCooks.enqueue(normal_cook);
            normal_cook->setStatus(CookStatus::Available);
            normal_cook->increasefatigue();
            msg += "Cook #" + to_string(normal_cook->getID()) + "Works over time";
        }

        Cook *vegan_cook = onBreakVeganCooks.peek();
        if(vegan_cook)
        {
            onBreakVeganCooks.dequeue();
            availableVeganCooks.enqueue(vegan_cook);
            vegan_cook->setStatus(CookStatus::Available);
            vegan_cook->increasefatigue();
            msg += "Cook #" + to_string(vegan_cook->getID()) + "Works over time";
        }
    }


    CurrentTimeStep++;
}

void Restaurant::Finish() {
    writeOutput();
    gui->PrintMessage("");
    gui->PrintMessage("Every thing is finished");
    isfinished = true;
}

void Restaurant::ShowStatusBar() {
    if(!isfinished)
    {
        gui->UpdateInterface();
        gui->PrintMessage("");
        gui->PrintMessage("TS: " + to_string(CurrentTimeStep));

        gui->PrintMessage(
            "Waiting Order VIP: " + to_string(waitingVIPOrders.getSize())
            + "            "
            + "Available Cook VIP: " + to_string(availableVIPCooks.getSize()));
        gui->PrintMessage("Waiting Order Vegan: "
                          + to_string(waitingVeganOrders.getSize())
                          + "            " + "Available Cook Vegan: "
                          + to_string(availableVeganCooks.getSize()));
        gui->PrintMessage("Waiting Order Normal: "
                          + to_string(waitingNormalOrders.getSize())
                          + "            " + "Available Cook Normal: "
                          + to_string(availableNormalCooks.getSize()));

        gui->PrintMessage(
            "Finished VIP: " + to_string(finishedVIPOrders.getSize()) + "    "
            + "Finished Normal: " + to_string(finishedNormalOrders.getSize())
            + "    "
            + "Finished Vegan: " + to_string(finishedVeganOrders.getSize()));
        if(!msg.empty())
        {
            gui->PrintMessage(msg);
        }
    }
}

void Restaurant::UpdateUI() {
    ShowStatusBar();
    gui->ResetDrawingList();
    
    for(int i = 0; i < cook_ids.getSize(); i++)
    {
        Cook *ptrcook = cookMap.get(cook_ids[i]);
        if(ptrcook->getStatus() == CookStatus::Available)
        {
            gui->AddToDrawingList(ptrcook);
        }
    }

    for(int i = 0; i < order_ids.getSize(); i++)
    {
        gui->AddToDrawingList(orderMap.get(order_ids[i]));
    }
    gui->UpdateInterface();
}

void Restaurant::simulate()
{
    mode = gui->getGUIMode();
    while(1)
    {
        UpdateUI();
        if(mode == MODE_SLNT)
        {
            while(!waitingNormalOrders.isEmpty() || !waitingVeganOrders.isEmpty()
               || !waitingVIPOrders.isEmpty()
               || !inServiceNormalOrders.isEmpty()
               || !inServiceVeganOrders.isEmpty()
               || !inServiceVIPOrders.isEmpty() || !eventsQueue.isEmpty())
            {
                ExecuteTimeStep();
            }
            Finish();
        }
        else if(mode == MODE_INTR)
        {
            // Waits for a mouse click for advances
            gui->waitForClick();
            if (!waitingNormalOrders.isEmpty() || !waitingVeganOrders.isEmpty()
                || !waitingVIPOrders.isEmpty()
                || !inServiceNormalOrders.isEmpty()
                || !inServiceVeganOrders.isEmpty()
               || !inServiceVIPOrders.isEmpty() || !eventsQueue.isEmpty())
            {
                ExecuteTimeStep();
            }
            else
            {
                Finish();
            }
        }
        else if(mode == MODE_STEP)
        {
            // waits for one second for advances
            Pause(1000);

            if(!waitingNormalOrders.isEmpty() || !waitingVeganOrders.isEmpty()
               || !waitingVIPOrders.isEmpty()
               || !inServiceNormalOrders.isEmpty()
               || !inServiceVeganOrders.isEmpty()
               || !inServiceVIPOrders.isEmpty() || !eventsQueue.isEmpty())
            {
                ExecuteTimeStep();
            }
            else
            {
                Finish();
            }
        }
    }
}