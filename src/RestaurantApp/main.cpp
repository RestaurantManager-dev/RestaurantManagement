#include "RestaurantLogic/Event/ArrivalEvent.hpp"
#include "RestaurantLogic/Event/CancellationEvent.hpp"
#include "RestaurantLogic/Event/PromotionEvent.hpp"
#include <iostream>

int main()
{
    PromotionEvent promoEvent(5);
    CancellationEvent cancelEvent(10);
    ArrivalEvent arrivalEvent(15);

    std::cout << "Promotion Event Time Step: " << promoEvent.getTimeStep()
              << ", Type: " << static_cast<int>(promoEvent.getType())
              << std::endl;
    std::cout << "Cancellation Event Time Step: " << cancelEvent.getTimeStep()
              << ", Type: " << static_cast<int>(cancelEvent.getType())
              << std::endl;
    std::cout << "Arrival Event Time Step: " << arrivalEvent.getTimeStep()
              << ", Type: " << static_cast<int>(arrivalEvent.getType())
              << std::endl;

    return 0;
}