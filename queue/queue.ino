#include <cppQueue.h>

uint16_t in = 0;


//we instantiate the queue, that would hold a maximum of 10 items, each one of them having the size of 2 bytes (siezof(unit16_t))
//FIFO: first in-first out
cppQueue  q(sizeof(in), 10, FIFO);  


void setup() 
{
  Serial.begin(9600);
  
  q.push(&in);    // we push the address of in in the queue; as in=0, 0 is stored in the queue
}


void loop() 
{
  uint16_t out;
  
  q.push(&(++in));// we increment in by 1 and the we push theb address of the incremented value into the queue
  q.pop(&out);//we pop the first element from the queue and store it in the variable out
  //as the queue works bade on FIFO, then we will retrieve the value of in that was psuhed first into the queue
  Serial.println(out);
  delay(2000);
}
