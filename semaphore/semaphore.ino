#include <mbed.h>
#include <rtos.h>

using namespace mbed;
using namespace rtos;
using namespace std::chrono_literals;

Semaphore two_slots(2); //create a semaphore with a ceiling of 2
Thread t1,t2,t3;

void test_thread(const char* name)
{
  while(true)
  {
    Serial.println(name);
    two_slots.acquire();
    Serial.println("It takes the semaphore\n");

    //simulate some work while the semaphore is being held
    ThisThread::sleep_for(1s);
   
    
    two_slots.release();
    Serial.println("It gives the semaphore\n");
  }
}

void setup() 
{
  Serial.begin(9600);
  t1.start(callback(test_thread, "Thread1"));
  delay(2000);
  t2.start(callback(test_thread, "Thread2"));
  delay(2000);
  t3.start(callback(test_thread, "Thread3"));
  delay(2000);
}

void loop() 
{}
