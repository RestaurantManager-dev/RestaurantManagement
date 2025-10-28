#pragma once

enum class OrderProgress
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
    int arrivalTime;
    int assignedTime;
    int finishTime;
    OrderProgress progress;
    int size;
    double price;

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
    OrderProgress getProgress() const;
    void setAssignedTime(int assignedTime);
    void setFinishTime(int finishTime);
    void setPrice(double price);
    void setProgress(OrderProgress progress);
    virtual OrderType getType() const = 0;
};
