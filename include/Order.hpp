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
    void setAssignedTime(int assignedTime);
    void setFinishTime(int finishTime);
    void setPrice(double price);
    void setStatus(OrderStatus Status);
    virtual OrderType getType() const = 0;
};
