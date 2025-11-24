#include "RestaurantApp/Resturant.h";

Resturant::Resturant() : AllOrders(100), AllCooks(100) {
    VIP_Orders_Overload_Thershold = 5;
    // Will be changed from load file
    Normal_Orders_Promote_Thershold = -1;
    CurrentTimestep = 0;
    loadFiles();
}

Resturant::~Resturant() {}

bool Resturant::isoverloaded() const
{
    return false;
}

void Resturant::loadFiles() {
    // CMAKE is stupid or I am.
    ifstream file("../../../input.txt");
    if(!file.is_open())
    {
        cout << "Can't open" << endl;
    }

    string line;
    
    // Number of cooks
    int N, G, V;
    int SN, SG, SV;
    int Bo;
    int BN, BG, BV;

    file >> N >> G >> V;
    file >> SN >> SG >> SV;
    file >> Bo >> BN >> BG >> BV;

    // Notice that we will need the pointer to the cooks/orders queue node not the class
    int id = 0;
    for(int i = 0; i < N; i++)
    {
        Cook *normalCook = new NormalCook(id, SN, BN, Bo);
        AvailableNormalCooks.enqueue(normalCook);
        AllCooks.add(id, normalCook);
        id++;
    }
    for(int i = 0; i < G; i++)
    {
        Cook *veganCook = new VeganCook(id, SG, BG, Bo);
        AvailableVeganCooks.enqueue(veganCook);
        AllCooks.add(id, veganCook);
        id++;
    }
    for(int i = 0; i < V; i++)
    {
        Cook *VipCook = new VIPCook(id, SV, BV, Bo);
        AvailableVIPCooks.enqueue(VipCook);
        AllCooks.add(id, VipCook);
        id++;
    }

    file >> Normal_Orders_Promote_Thershold;

    int m;
    file >> m;
    for (int i = 0; i < m; i++) {
        char evtype;
        file >> evtype;
        if(evtype == 'R')
        {
            char type;
            int artime, id, size, total;
            file >> type >> artime >> id >> size >> total;
            if(type == 'N')
            {
                Order *order = new NormalOrder(id, artime, size, total);
                WaitingNormalOrders.insert(order);
                AllOrders.add(id, order);
            }
            else if (type == 'G') {
                Order *order = new VeganOrder(id, artime, size, total);
                WaitingVeganOrders.insert(order);
                AllOrders.add(id, order);
            }
            else if(type == 'V')
            {
                Order *order = new VIPOrder(id, artime, size, total);
                WaitingVIPOrders.insert(order);
                AllOrders.add(id, order);
            }

            // TODO: FIX
            Event *event = new ArrivalEvent(artime);
            Events.insert(event);
        }
        else if (evtype == 'X'){
            string s;
            file >> s;
            // TODO: FIX
            Event *event = new CancellationEvent(0);
            Events.insert(event);
        }
        else if (evtype == 'P') {
            string s;
            file >> s;
            // TODO: FIX
            Event *event = new PromotionEvent(0);
            Events.insert(event);
        }
    }

    file.close();
}

void Resturant::WriteOutput() const {}

void Resturant::excuteTimestep() {}

void Resturant::simulate() {}
