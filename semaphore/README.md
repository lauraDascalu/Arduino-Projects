# Multithreaded Semaphore Management (RTOS)

This project demonstrates a multithreaded program using a semaphore to manage controlled access to a shared resource. Developed with the **Mbed** and **RTOS** libraries, it highlights key concepts in multithreading and synchronization within embedded systems.

---

## Overview

The program uses:
- **Counting Semaphore**: Initialized with a count of 2, allowing up to 2 threads to access the shared resource simultaneously.
- **Three Threads**: Each thread attempts to acquire the semaphore, perform work, and release the semaphore.

This setup simulates real-world scenarios where multiple processes or tasks need synchronized access to limited resources.

---

## Program Workflow

1. **Semaphore Initialization**: A counting semaphore is created with an initial count and a maximum count of 2, enabling controlled access for up to 2 threads at a time.
2. **Thread Behavior**:
   - Each thread tries to acquire the semaphore.
   - Once acquired, it prints a message indicating it has started its task.
   - The thread simulates work by sleeping for a set period.
   - After completing its task, it releases the semaphore and prints a completion message.

This coordinated access ensures orderly and limited access to the shared resource, with only 2 threads accessing it at a time while the third waits.

---

## Example Output
![image](https://github.com/user-attachments/assets/b5b20e54-9253-4fd0-aa46-19e10add1008)

---

## Code Usage
1. **Library Requirement:**  Ensure both the Mbed and RTOS libraries are installed and configured in your development environment.
2. **Upload the Code:** Flash the code onto your target microcontroller.
3. **Observe the Output:** Use a serial monitor to view thread interactions and semaphore usage in real time.

---
## Dependencies
  - **Mbed Library:** Provides a foundational set of functions and classes for embedded programming.
  - **RTOS Library:** Offers thread and semaphore management for real-time scheduling.

## Key Takeaways
This project provides an introductory understanding of:
  - Multithreading and concurrent access to resources.
  - Semaphore-based synchronization for managing shared resources.
  - Real-time task scheduling in embedded systems using Mbed and RTOS.

