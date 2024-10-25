# Signaling & Communication (RTOS)
This project demonstrates basic signaling and communication concepts within a Real-Time Operating System (RTOS) using a queue. A simple queue is implemented with the `cppQueue` library to manage data flow in a First In, First Out (FIFO) manner.

---

## Overview

The code initializes a queue with the following properties:
- **Maximum items**: 10
- **Item size**: 2 bytes each (unsigned integers)

This implementation showcases queue operations such as adding and removing items, with the oldest value in the queue being retrieved and printed upon removal.

---
 
 ## Queue Functionality

The program simulates a FIFO queue operation with the following steps:

1. **Initialization**: The queue begins with a single value (`in=0`).
2. **Increment and Enqueue**: The value of `in` is incremented and then added to the queue.
3. **Dequeue and Print**: The oldest value in the queue is removed and stored in the variable `out`, which is then printed to the serial monitor.

The result displayed in the serial monitor is a sequence of incremented numbers starting from `1`.

---

### Example Serial Monitor Output

The serial monitor will show a sequence of incremented values as they are added to and removed from the queue. This output represents the basic FIFO behavior, with values appearing in the order they were added.

![image](https://github.com/user-attachments/assets/00bd476e-e78f-444b-9ddf-e947c42b6e61)

---
## Code Usage

1. **Library Requirement**: Ensure the `cppQueue` library is installed in your Arduino IDE.
2. **Upload the Code**: Upload the code to your microcontroller, such as an Arduino Nano RP2040.
3. **Monitor Output**: Open the serial monitor to observe the output sequence of incremented numbers as they are enqueued and dequeued.

---

## Dependencies

- **cppQueue Library**: This library is used to manage the queue and provides the necessary functions to initialize, enqueue, dequeue, and manage queue size.
## Key Takeaways

This project provides an introductory understanding of:
- Queue management in embedded systems.
- First In, First Out (FIFO) data handling.
- Real-time data handling within an RTOS framework, using basic signaling and communication techniques.

