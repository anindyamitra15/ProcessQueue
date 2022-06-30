#include <Arduino.h>
#include <ProcessQueue.h>

ProcessQueue p_queue;

void_function event = []()
{
  Serial.println("Event Triggered");
  delay(3000);
  Serial.println("Event Serviced");
};

void func1()
{
  Serial.println("func1()");
}

void ISR_func()
{
  p_queue.push(event);
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
}

void loop()
{
  p_queue.loop();
  // static uint32_t last_time = 0;
  // if (millis() - last_time > 500)
  // {
  //   Serial.println(queue.size());
  //   last_time = millis();
  // }
}