#include <Arduino.h>
#include <CircularQueue.h>

CircularQueue queue;

// #include <ProcessQueue.h>

// ProcessQueue queue;

// void_function event = []()
// {
//   Serial.println("Event Triggered");
//   delay(3000);
//   Serial.println("Event Serviced");
// };

void ISR_func()
{
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(
      digitalPinToInterrupt(2),
      ISR_func, // element is pushed to the queue through interrupt
      FALLING);

  queue.push(3);
  queue.push(4);
  queue.push(5);

  queue.display();
  Serial.println(queue.pop());
  queue.display();

  queue.push(6);
  queue.display();
  queue.push(7); // should trigger overflow
  queue.display();

  Serial.println(queue.size());
  Serial.println(queue.pop());
  Serial.println(queue.pop());
  Serial.println(queue.pop());
  Serial.println(queue.size());
}

void loop()
{
  // if (!queue.isEmpty())
  // {
  //   queue.pop();
  // }
  // static uint32_t last_time = 0;
  // if (millis() - last_time > 500)
  // {
  //   Serial.println(queue.size());
  //   last_time = millis();
  // }
}