<h1>CIE 205 Project: Restaurant Management System</h1>

[cite_start]**Institution:** University of Science and Technology, Zewail City [cite: 1]
[cite_start]**Program:** Communication and Information Engineering [cite: 2]
[cite_start]**Course:** CIE 205: Fundamentals of Computer Programming / Data Structures and Algorithms [cite: 3, 4]

---

## 📝 Project Overview

[cite_start]This project is a complete object-oriented C++ simulation of a restaurant's kitchen system[cite: 12, 19]. [cite_start]The goal is to use custom-built data structures to model the restaurant's operations, assess service performance, and determine the optimal rules for serving orders to maximize customer satisfaction[cite: 13, 17, 18, 19].

[cite_start]The simulation is built from scratch, including all necessary data structures implemented with C++ Templates[cite: 12, 226]. [cite_start]It processes events from an input file, manages cooks and orders, and generates a detailed output file with performance statistics[cite: 106].

## ✨ Core Features

* [cite_start]**Discrete Event Simulation:** The system state is updated at discrete time steps (1 unit each)[cite: 85].
* **Order Management:** Manages three types of orders:
    * [cite_start]**VIP Orders** [cite: 35]
    * [cite_start]**Vegan Orders** [cite: 36]
    * [cite_start]**Normal Orders** [cite: 37]
* **Cook Management:** Manages three types of specialized cooks:
    * [cite_start]**VIP Cooks** [cite: 44]
    * [cite_start]**Vegan Cooks** [cite: 45]
    * [cite_start]**Normal Cooks** [cite: 46]
* [cite_start]**Cook Breaks:** Cooks must take a break of a specified duration after serving a set number of consecutive orders[cite: 47].
* [cite_start]**Event Handling:** Processes a sorted list of events from an input file[cite: 127, 133], including:
    * [cite_start]**R:** Order Arrival [cite: 129, 138]
    * [cite_start]**X:** Order Cancellation (for Normal orders) [cite: 130, 145]
    * [cite_start]**P:** Order Promotion (for Normal orders) [cite: 131, 149]
* **Special Order Services:** Normal orders have unique capabilities:
    * [cite_start]They can be canceled at any time before being assigned to a cook[cite: 79].
    * [cite_start]They can be promoted to VIP if the customer pays an extra fee[cite: 78].
    * [cite_start]They are automatically promoted to VIP if they wait longer than a specified time (`AutoP`)[cite: 80, 123].
* [cite_start]**Statistics Generation:** Produces an output file containing per-order details (Finish Time, ID, Arrival Time, Wait Time, Service Time) [cite: 169] [cite_start]and summary statistics[cite: 178].

## ⚙️ Simulation Logic & Prioritization

[cite_start]The simulation's core logic determines which waiting order is served when a cook becomes available[cite: 54].

### Order Assignment Criteria

1.  **VIP Orders:** Served with the highest priority by any available cook, in this order:
    * [cite_start]VIP Cooks $\rightarrow$ Normal Cooks $\rightarrow$ Vegan Cooks [cite: 56, 57]
    * [cite_start]A less-preferred cook type is only used if all higher-priority cooks are busy[cite: 58].

2.  **Vegan Orders:**
    * [cite_start]Can **only** be served by available Vegan cooks[cite: 60].
    * [cite_start]If all Vegan cooks are busy, the order must wait[cite: 61].

3.  **Normal Orders:** Served by any non-Vegan cook, in this order:
    * [cite_start]Normal Cooks $\rightarrow$ VIP Cooks [cite: 63]
    * [cite_start]A VIP cook is only used if all Normal cooks are busy[cite: 64].

### Intra-Type Prioritization

When multiple orders of the *same type* are waiting:

* [cite_start]**Vegan & Normal Orders:** Served based on arrival time (First-Come, First-Served)[cite: 72].
* [cite_start]**VIP Orders:** Served based on a priority equation that considers Order Arrival Time, Order Price, and Order Size[cite: 73, 74, 75, 76].

## 🖥️ Program Interface Modes

[cite_start]The program supports three distinct operation modes, selected by the user at startup[cite: 197, 198].

1.  **Interactive Mode:**
    * [cite_start]Displays the current system state at each time step[cite: 201].
    * [cite_start]Pauses the simulation, waiting for a user's mouse click to advance to the next step[cite: 201].
    * [cite_start]The screen displays the current time, counts of waiting orders and available cooks, and orders served in the last step[cite: 203, 204, 205, 206, 208].

2.  **Step-by-Step Mode:**
    * [cite_start]Identical to Interactive Mode, but it advances to the next time step automatically after one second[cite: 210]. [cite_start]No mouse click is required[cite: 210].

3.  **Silent Mode:**
    * [cite_start]No graphics are displayed[cite: 212].
    * [cite_start]The program performs the full simulation and generates the final output file as its only result[cite: 212].

[cite_start]Regardless of the mode, the output file is always generated at the end of the simulation[cite: 217].

## 🛠️ Technical Specifications

* [cite_start]**Language:** C++[cite: 12].
* [cite_start]**Data Structures:** All data structures are implemented from scratch using C++ **Templates**[cite: 12, 222].
* **Constraints:**
    * [cite_start]The use of C++ STL data structure implementations (like `std::vector`, `std::list`, `std::queue`) is **not allowed**[cite: 225].
    * [cite_start]No global variables are used[cite: 230].
    * [cite_start]The program is designed for modularity, separating simulation logic, file I/O, and data structure implementations[cite: 310].

## 👥 Team Members

* Youssef Mohamed 202400956
* Mazen Salem 202400447
* Mahmoud Abdelwabab 202402046
* Ahmed Nader 202401010
