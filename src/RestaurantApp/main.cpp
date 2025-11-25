#include "DataStructures/DataStructures.hpp"
#include "RestaurantLogic/Restaurant.hpp"
#include "RestaurantLogic/RestaurantLogic.hpp"
#include <iostream>

int main()
{
    Restaurant restaurant;
    restaurant.loadFiles(INPUT_FILE_PATH);
    restaurant.simulate();
    return 0;
}