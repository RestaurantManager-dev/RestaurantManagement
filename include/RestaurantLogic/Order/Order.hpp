#pragma once

enum class OrderStatus
{
    Waiting,
    InService,
    Finished,
    Cancelled
};

enum class OrderType
{
    Normal,
    Vegan,
    VIP
};

class Order
{
private:
    int ID;
    int size;
    double price;

    int arrivalTime;
    int assignedTime;
    int finishTime;
    OrderStatus status;

    void *queueNode;

protected:
    Order(int ID, int arrivalTime, int size, double price);

public:
    virtual ~Order() = default;
    int getID() const;
    int getArrivalTime() const;
    int getAssignedTime() const;
    int getFinishTime() const;
    int getWaitingTime() const;
    int getServiceTime() const;
    int getSize() const;
    double getPrice() const;
    OrderStatus getStatus() const;
    void *getQueueNode() const;
    void setAssignedTime(int assignedTime);
    void setFinishTime(int finishTime);
    void setPrice(double price);
    void setStatus(OrderStatus status);
    void setQueueNode(void *node);
    virtual OrderType getType() const = 0;
};
