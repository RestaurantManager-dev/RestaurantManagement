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

void Restaurant::writeOutput() const {}

void Restaurant::executeEvents() {
    if(eventsQueue.isEmpty())
        return;

    Event *event = eventsQueue.peek();
    while(event->getTimeStep() == this->CurrentTimeStep)
    {
        if(event->getType() == EventType::Arrival)
        {
            ArrivalEvent* Arevent = dynamic_cast<ArrivalEvent *>(event);
            if(Arevent->getOrderType() == OrderType::Normal)
            {
                Order *order = new NormalOrder(Arevent->getorderid(), Arevent->getTimeStep(), Arevent->getordersize(), Arevent->getordertotal());
                waitingNormalOrders.enqueue(order);
                orderMap.add(order->getID(), order);
            }
            else if(Arevent->getOrderType() == OrderType::Vegan)
            {
                Order *order = new VeganOrder(
                    Arevent->getorderid(), Arevent->getTimeStep(),
                    Arevent->getordersize(), Arevent->getordertotal());
                waitingVeganOrders.enqueue(order);
                orderMap.add(order->getID(), order);
            }
            else
            {
                Order *order = new VIPOrder(
                    Arevent->getorderid(), Arevent->getTimeStep(),
                    Arevent->getordersize(), Arevent->getordertotal());
                waitingVIPOrders.insert(order);
                orderMap.add(order->getID(), order);
            }
        }
        else if(event->getType() == EventType::Cancellation)
        {
            CancellationEvent *Cevent = dynamic_cast<CancellationEvent *>(event);
            int orderId = Cevent->getOrderId();
            Order *order = orderMap.get(orderId);
            waitingNormalOrders.remove(order);
            orderMap.remove(orderId);
            delete order;
        }
        else if(event->getType() == EventType::Promotion)
        {
            // TODO
        }
    }
}

void Restaurant::simulate() {}