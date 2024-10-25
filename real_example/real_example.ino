#include <mbed.h>
#include <rtos.h>
#include <WiFiNINA.h>

using namespace mbed;
using namespace rtos;

// create a binary semaphore 
Semaphore lockSemaphore(1);

Thread lockThread;
Thread unlockThread;

void lockTask() {
    while (true) 
    {
        // simulate receiving a lock command
        Serial.println("Lock command received\n");

        // acquire the semaphore to lock the door
        if (lockSemaphore.try_acquire_for(10000)) 
        {
            // perform the lock action
            digitalWrite(LEDR, HIGH);
            Serial.println("Door locked\n");

            // simulate the time taken to lock the door
            ThisThread::sleep_for(1000);

            // release the semaphore
            lockSemaphore.release();
        } 
        else 
        {
            Serial.println("Could not lock, semaphore not available\n");
        }

        // wait before trying again
        ThisThread::sleep_for(5000);
    }
}

void unlockTask() {
    while (true) 
    {
        // simulate receiving an unlock command
        Serial.println("Unlock command received\n");

        // acquire the semaphore to unlock the door
        if (lockSemaphore.try_acquire_for(10000)) {
            // perform the unlock action
            digitalWrite(LEDR, LOW);
            Serial.println("Door unlocked\n");

            // simulate the time taken to unlock the door
            ThisThread::sleep_for(1000);

            // release the semaphore
            lockSemaphore.release();
        } 
        else 
        {
            Serial.println("Could not unlock, semaphore not available\n");
        }

        // wait before trying again
        ThisThread::sleep_for(5000);
    }
}

void setup() {
    Serial.begin(9600);
    
    pinMode(LEDR, OUTPUT);
    digitalWrite(LEDR, LOW);

    // start the lock and unlock threads
    lockThread.start(lockTask);
    unlockThread.start(unlockTask);
}

void loop() {
    // empty loop as tasks are handled by threads
}
