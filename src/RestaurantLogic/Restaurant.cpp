#include "RestaurantLogic/Restaurant.hpp"

#include <iostream>

Restaurant::Restaurant() : orderMap(10007), cookMap(10007) {}

void Restaurant::simulate()
{
    std::cout << "\n=== [SIMULATION START] ===\n";

    // =========================================================================
    // 1. DATA GENERATION & ARRIVAL
    //    Using specific constructors: new NormalOrder(...), new VIPOrder(...)
    // =========================================================================
    std::cout << "\n--- Step 1: Orders Arriving & Cooks Logging In ---\n";

    // --- Create Normal Orders (ID, ArrivalTime, Size, Price) ---
    NormalOrder *nOrder1 = new NormalOrder(101, 5, 2, 60.0);
    NormalOrder *nOrder2 = new NormalOrder(102, 8, 4, 120.0);

    // Enqueue them (Implicitly converts NormalOrder* to Order*)
    waitingNormalOrders.enqueue(nOrder1);
    waitingNormalOrders.enqueue(nOrder2);
    std::cout << "[Arrival] Normal Order " << nOrder1->getID() << " & "
              << nOrder2->getID() << " added to Waiting Queue.\n";

    // --- Create VIP Orders (Demonstrating Priority) ---
    // ID 201 arrives at time 20. ID 202 arrives at time 2.
    // Logic: Lower ArrivalTime = Higher Priority.
    VIPOrder *vOrder1 = new VIPOrder(201, 20, 1, 200.0);
    VIPOrder *vOrder2 = new VIPOrder(202, 2, 3, 450.0);

    // Insert into PriorityQueue
    waitingVIPOrders.insert(vOrder1);
    waitingVIPOrders.insert(vOrder2);
    std::cout
        << "[Arrival] VIP Orders 201 (Time 20) & 202 (Time 2) added to PQ.\n";

    // --- Create Cooks ---
    // Assuming Cook constructor: (ID, Type, Speed, BreakDuration)
    Cook *nCook = new NormalCook(1, 5, 2, 10);
    Cook *vCook = new VIPCook(2, 6, 3, 8); // VIP Cook

    availableNormalCooks.enqueue(nCook);
    availableVIPCooks.enqueue(vCook);
    std::cout << "[Staff] Cooks " << nCook->getID() << " (Normal) & "
              << vCook->getID() << " (VIP) are available.\n";

    // =========================================================================
    // 2. SERVING (Moving from Waiting Queue -> InService Queue)
    // =========================================================================
    std::cout << "\n--- Step 2: Service Assignment ---\n";

    // --- Serve a Normal Order ---
    if(!waitingNormalOrders.isEmpty() && !availableNormalCooks.isEmpty())
    {
        // 1. Dequeue Order (Removes from waitingNormalOrders, clears pointers)
        Order *ord = waitingNormalOrders.dequeue();

        // 2. Dequeue Cook
        Cook *ck = availableNormalCooks.dequeue();

        // 3. Update Status
        ord->setStatus(OrderStatus::InService);
        ord->setAssignedTime(10); // Current simulation time

        // 4. Enqueue to InService (Uses the SAME next/prev pointers inside ord)
        inServiceNormalOrders.enqueue(ord);

        std::cout << "[Service] Normal Cook " << ck->getID()
                  << " is serving Order " << ord->getID() << ".\n";
    }

    // --- Serve a VIP Order ---
    if(!waitingVIPOrders.isEmpty() && !availableVIPCooks.isEmpty())
    {
        // 1. Extract Highest Priority (Should be vOrder2 because ArrivalTime 2
        // < 20)
        Order *vipOrd = waitingVIPOrders.extract();

        // 2. Dequeue Cook
        Cook *vipCk = availableVIPCooks.dequeue();

        // 3. Update Status
        vipOrd->setStatus(OrderStatus::InService);
        vipOrd->setAssignedTime(10);

        // 4. Enqueue to InService
        inServiceVIPOrders.enqueue(vipOrd);

        std::cout << "[Service] VIP Cook " << vipCk->getID()
                  << " is serving Order " << vipOrd->getID()
                  << " (Priority Winner).\n";
    }

    // =========================================================================
    // 3. FINISHING (Moving from InService Queue -> Finished Queue)
    // =========================================================================
    std::cout << "\n--- Step 3: Finishing Orders ---\n";

    // Use a while loop to finish all currently served normal orders
    while(!inServiceNormalOrders.isEmpty())
    {
        // 1. Dequeue from Service
        Order *finishedOrd = inServiceNormalOrders.dequeue();

        // 2. Update Status
        finishedOrd->setStatus(OrderStatus::Finished);
        finishedOrd->setFinishTime(25); // Current simulation time

        // 3. Enqueue to Finished Queue (The generic list for all finished
        // items)
        finishedOrders.enqueue(finishedOrd);

        // 4. Return Cook (In a real logic, you'd map Order->Cook to know which
        // one to free)
        availableNormalCooks.enqueue(nCook);

        std::cout << "[Finished] Order " << finishedOrd->getID()
                  << " moved to Finished Queue.\n";
    }

    // =========================================================================
    // 4. FINAL REPORT
    // =========================================================================
    std::cout << "\n--- Final Queue States ---\n";
    std::cout << "Waiting Normal Queue Size: " << waitingNormalOrders.getSize()
              << " (Expected: 1, Order 102)\n";
    std::cout << "InService Normal Queue:    "
              << inServiceNormalOrders.getSize() << " (Expected: 0)\n";
    std::cout << "Finished Queue Size:       " << finishedOrders.getSize()
              << " (Expected: 1, Order 101)\n";

    // Demonstrate Peek works on the generic Finished Queue
    if(!finishedOrders.isEmpty())
    {
        std::cout << "First Finished Order ID:   "
                  << finishedOrders.peek()->getID() << "\n";
    }

    std::cout << "=== [SIMULATION END] ===\n";
}