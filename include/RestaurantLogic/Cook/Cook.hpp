#pragma once
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

    void setStatus(CookStatus status);
    void setOrdersServed(int count);
    void setCurrentOrderID(int orderID);
    void setAssignedTime(int time);
    void setBreakStartTime(int time);

    bool serveOrder();

    virtual CookType getType() const = 0;
};