#include <Arduino.h>
#include <ProcessQueue.h>

ProcessQueue queue;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(queue.size());
  queue.push(
    []()
    { 
      Serial.println("function 1"); 
    }
    );
  queue.push(
    []()
    {
      Serial.println("function 2");
    }
    );
  queue.push(
    []()
    {
      Serial.println("function 3"); 
    }
    );

  Serial.println(queue.size());
  queue.pop();
  Serial.println(queue.size());
  queue.clear();
  Serial.println(queue.size());
}

void loop()
{
  // put your main code here, to run repeatedly:
}