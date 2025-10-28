<h1>CIE 205 Project: Restaurant Management System</h1>

**Institution:** University of Science and Technology, Zewail City
**Program:** Communication and Information Engineering
**Course:** CIE 205: Fundamentals of Computer Programming / Data Structures and Algorithms

---

## 📝 Project Overview

This project is a complete object-oriented C++ simulation of a restaurant's kitchen system. The goal is to use custom-built data structures to model the restaurant's operations, assess service performance, and determine the optimal rules for serving orders to maximize customer satisfaction.

The simulation is built from scratch, including all necessary data structures implemented with C++ Templates. It processes events from an input file, manages cooks and orders, and generates a detailed output file with performance statistics.

## ✨ Core Features

* **Discrete Event Simulation:** The system state is updated at discrete time steps (1 unit each).
* **Order Management:** Manages three types of orders:
    * **VIP Orders** 
    * **Vegan Orders** 
    * **Normal Orders** 
* **Cook Management:** Manages three types of specialized cooks:
    * **VIP Cooks**
    * **Vegan Cooks**
    * **Normal Cooks**
* **Cook Breaks:** Cooks must take a break of a specified duration after serving a set number of consecutive orders.
* **Event Handling:** Processes a sorted list of events from an input file, including:
    * **R:** Order Arrival
    * **X:** Order Cancellation (for Normal orders)
    * **P:** Order Promotion (for Normal orders)
* **Special Order Services:** Normal orders have unique capabilities:
    * They can be canceled at any time before being assigned to a cook.
    * They can be promoted to VIP if the customer pays an extra fee.
    * They are automatically promoted to VIP if they wait longer than a specified time (`AutoP`).
* **Statistics Generation:** Produces an output file containing per-order details (Finish Time, ID, Arrival Time, Wait Time, Service Time) and summary statistics.

## ⚙️ Simulation Logic & Prioritization

The simulation's core logic determines which waiting order is served when a cook becomes available.

### Order Assignment Criteria

1.  **VIP Orders:** Served with the highest priority by any available cook, in this order:
    * VIP Cooks $\rightarrow$ Normal Cooks $\rightarrow$ Vegan Cooks
    * A less-preferred cook type is only used if all higher-priority cooks are busy.

2.  **Vegan Orders:**
    * Can **only** be served by available Vegan cooks.
    * If all Vegan cooks are busy, the order must wait.

3.  **Normal Orders:** Served by any non-Vegan cook, in this order:
    * Normal Cooks $\rightarrow$ VIP Cooks 
    * A VIP cook is only used if all Normal cooks are busy.

### Intra-Type Prioritization

When multiple orders of the *same type* are waiting:

* **Vegan & Normal Orders:** Served based on arrival time (First-Come, First-Served).
* **VIP Orders:** Served based on a priority equation that considers Order Arrival Time, Order Price, and Order Size.

## 🖥️ Program Interface Modes

The program supports three distinct operation modes, selected by the user at startup.

1.  **Interactive Mode:**
    * Displays the current system state at each time step.
    * Pauses the simulation, waiting for a user's mouse click to advance to the next step.
    * The screen displays the current time, counts of waiting orders and available cooks, and orders served in the last step.

2.  **Step-by-Step Mode:**
    * Identical to Interactive Mode, but it advances to the next time step automatically after one second. No mouse click is required.

3.  **Silent Mode:**
    * No graphics are displayed.
    * The program performs the full simulation and generates the final output file as its only result.

Regardless of the mode, the output file is always generated at the end of the simulation.

## 🛠️ Technical Specifications

* **Language:** C++.
* **Data Structures:** All data structures are implemented from scratch using C++ **Templates**.
* **Constraints:**
    * The use of C++ STL data structure implementations (like `std::vector`, `std::list`, `std::queue`) is **not allowed**.
    * No global variables are used.
    * The program is designed for modularity, separating simulation logic, file I/O, and data structure implementations.

## 👥 Team Members

* Youssef Mohamed 202400956
* Mazen Salem 202400447
* Mahmoud Abdelwabab 202402046
* Ahmed Nader 202401010
