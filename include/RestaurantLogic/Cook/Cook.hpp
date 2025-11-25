#pragma once
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/Queue.hpp"

enum class CookType
{
    Normal,
    Vegan,
    VIP
};

enum class CookStatus
{
    Available,
    Busy,
    OnBreak
};

class Cook : public QueueNode<Cook *>
{
private:
    int ID;
    int speed;
    int breakDuration;
    int ordersBeforeBreak;

    CookStatus status;
    int ordersServed;
    int currentOrderID;
    int currentOrderSize;
    int endTimeOfCurrentOrder;
    int assignedTime;
    int breakStartTime;

protected:
    Cook(int ID, int speed, int breakDuration, int ordersBeforeBreak);

public:
    virtual ~Cook() = default;

    int getID() const;
    int getSpeed() const;
    CookStatus getStatus() const;
    int getOrdersServed() const;
    int getBreakDuration() const;
    int getOrdersBeforeBreak() const;
    int getCurrentOrderID() const;
    int getAssignedTime() const;
    int getBreakStartTime() const;
    int getCurrentOrderSize() const;

    void setStatus(CookStatus status);
    void setOrdersServed(int count);
    int getEndTimeOfCurrentOrder() const;
    void setCurrentOrderID(int orderID);
    void setAssignedTime(int time);
    void setBreakStartTime(int time);
    void setCurrentOrderSize(int size);

    bool serveOrder();

    virtual CookType getType() const = 0;

    class FinishComparator : public PriorityComparator<Cook *>
    {
    public:
        bool operator()(Cook *a, Cook *b) const override
        {
            int aFinishTime =
                a->getAssignedTime() + (a->getCurrentOrderID() == -1 ? 0 : a->getCurrentOrderSize() / a->getSpeed());
            int bFinishTime =
                b->getAssignedTime() + (b->getCurrentOrderID() == -1 ? 0 : b->getCurrentOrderSize() / b->getSpeed());
            return aFinishTime < bFinishTime;
        }
    };
};