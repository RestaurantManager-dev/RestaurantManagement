#pragma once
#include "DataStructures/HashMap.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "RestaurantLogic/RestaurantLogic.hpp"


class OrderComparitor : PriorityComparator <Order *>
{
public:
    bool operator()(Order *a, Order *b) const override
    {
        return a->getArrivalTime() < b->getArrivalTime();
    }
};


class VIPOrderComparitor : PriorityComparator<Order *>
{
public:
    bool operator()(Order *a, Order *b) const override
    {
        int scorea = -a->getArrivalTime() + a->getPrice() + a->getSize();
        int scoreb = -b->getArrivalTime() + b->getPrice() + b->getSize();
        return scorea > scoreb;
    }
};


class OrderFinishComparitor : PriorityComparator<Order *>
{
public:
    bool operator()(Order *a, Order *b) const override
    {
        return a->getFinishTime() < b->getFinishTime();
    }
};


class CookFinishCompare : PriorityComparator<Cook *>
{
    public:
    bool operator()(Cook *a, Cook *b) const override
    {
        return a->getEndtimeOfCurrentOrder() < b->getEndtimeOfCurrentOrder();
    }
};

class Resturant
{
public:
    Resturant();
    ~Resturant();
    
    bool isoverloaded() const;


    void loadFiles();
    void WriteOutput() const;
    
    void excuteTimestep();
    void simulate();


private:
    int VIP_Orders_Overload_Thershold;
    int Normal_Orders_Promote_Thershold;
    int CurrentTimestep;

    // PriorityQueue<Event* > Events;

    HashMap<Order *> AllOrders;
    
    PriorityQueue<Order *, OrderComparitor> WaitingNormalOrders;
    PriorityQueue<Order *, OrderComparitor> WaitingVeganOrders;
    PriorityQueue<Order *, VIPOrderComparitor> WaitingVIPOrders;

    // For non-normal orders
    PriorityQueue<Order *, OrderFinishComparitor> InServiceOrders;
    /*
     * Notice that we have separate InService queues for normal orders to
     * facilitate the interuption and finishing process for the same end of the
     * priority queue.
    */

    /*
    * Notice that we must store the cook who is currently serving this order.
    */
    PriorityQueue<Order *, OrderFinishComparitor> InServiceNormalOrders;

    Queue<Order *> FinishedOrders;

    

    HashMap<Cook *> AllCooks;

    Queue<Cook *> AvailableVIPCooks;
    Queue<Cook *> AvailableVeganCooks;
    Queue<Cook *> AvailableNormalCooks;

    PriorityQueue<Cook *, CookFinishCompare> InServiceCooks;
    
    Queue<Cook *> InBreakCooks;

};
