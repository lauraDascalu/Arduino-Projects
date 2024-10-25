#include <mbed.h>

using namespace mbed;
using namespace rtos;
using namespace std::chrono_literals;

Thread thread1;
Thread thread2;

Mutex mutex;

void test(const char *name) {
    while (true) {
        // Lock the mutex to protect the shared resource
        mutex.lock();
        
        Serial.print(name);
        Serial.print(" has taken the mutex.\n");
        
        delay(500);
        
        mutex.unlock(); // Unlock the mutex
        delay(500); 
    }
}


void setup() {
    
    thread1.start(callback(test, "Thread 1"));
    thread2.start(callback(test, "Thread 2"));
}

void loop() {
}
