#include "RestaurantLogic/Restaurant.hpp"


Restaurant::Restaurant() : orderMap(10007), cookMap(10007)
{
    VIPOrdersOverloadThreshold = 5;
    // Will be changed from load file
    NormalOrdersPromoteThreshold = -1;
    CurrentTimeStep = 0;
}

bool Restaurant::isOverloaded() const
{
    return waitingVIPOrders.getSize() >= VIPOrdersOverloadThreshold;
}

void Restaurant::loadFiles(std::string filePath)
{
    ifstream file(filePath);
    if(!file.is_open())
    {
        cout << "Can't open" << std::endl;
    }
    cout << "File opened successfully" << std::endl;
    string line;

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
        id++;
    }
    for(int i = 0; i < G; i++)
    {
        Cook *veganCook = new VeganCook(id, SG, BG, Bo);
        availableVeganCooks.enqueue(veganCook);
        cookMap.add(id, veganCook);
        id++;
    }
    for(int i = 0; i < V; i++)
    {
        Cook *VipCook = new VIPCook(id, SV, BV, Bo);
        availableVIPCooks.enqueue(VipCook);
        cookMap.add(id, VipCook);
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

            Event *event = new ArrivalEvent(artime);
            dynamic_cast<ArrivalEvent*>(event)->setOrderDetails(
                                                                static_cast<OrderType>(type),
                                                                id, size, total);
            eventsQueue.insert(event);
        }
        else if(evtype == 'X')
        {
            int cantime, id;
            file >> cantime >> id;
            Event *event = new CancellationEvent(cantime);
            dynamic_cast<CancellationEvent *>(event)->setOrderId(id);

            eventsQueue.insert(event);
        }
        else if(evtype == 'P')
        {
            int protime, id, prototal;
            file >> protime >> id >> prototal;
           
            Event *event = new PromotionEvent(protime);
            dynamic_cast<PromotionEvent *>(event)->setOrderID(id);
            dynamic_cast<PromotionEvent *>(event)->setExtraMoney(prototal);

            eventsQueue.insert(event);
        }
    }

    file.close();
}

void Restaurant::writeOutput() const {}

void Restaurant::excuteTimeStep() {
    /*if(type == 'N')
    {
        Order *order = new NormalOrder(id, artime, size, total);
        waitingNormalOrders.enqueue(order);
        orderMap.add(id, order);
    }
    else if(type == 'G')
    {
        Order *order = new VeganOrder(id, artime, size, total);
        waitingVeganOrders.enqueue(order);
        orderMap.add(id, order);
    }
    else if(type == 'V')
    {
        Order *order = new VIPOrder(id, artime, size, total);
        waitingVIPOrders.insert(order);
        orderMap.add(id, order);
    }*/
}

void Restaurant::simulate() {}