#include "RestaurantApp/Resturant.h";

Resturant::Resturant() : AllOrders(100), AllCooks(100) {
    VIP_Orders_Overload_Thershold = 5;
    // Will be changed from load file
    Normal_Orders_Promote_Thershold = -1;
    CurrentTimestep = 0;
}

Resturant::~Resturant() {}

bool Resturant::isoverloaded() const
{
    return false;
}

void Resturant::loadFiles() {

}

void Resturant::WriteOutput() const {}

void Resturant::excuteTimestep() {}

void Resturant::simulate() {}
