#include <Arduino.h>
#include <ProcessQueue.h>

ProcessQueue queue;

void_function event = []()
{
  Serial.println("Event Triggered");
  delay(3000);
  Serial.println("Event Serviced");
};

void setup()
{
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println();

  attachInterrupt(
      digitalPinToInterrupt(2), []()
      { queue.push(event); }, //element is pushed to the queue through interrupt
      FALLING);

  Serial.println(queue.size());
  queue.push(
      []()
      {
        Serial.println("function 1");
      });
  queue.push(
      []()
      {
        Serial.println("function 2");
        delay(200);
        Serial.println("function 2 ends");
      });
  queue.push(
      []()
      {
        Serial.println("function 3");
      });
}

void loop()
{
  if (!queue.isEmpty())
  {
    queue.pop();
  }
  static uint32_t last_time = 0;
  if (millis() - last_time > 500)
  {
    Serial.println(queue.size());
    last_time = millis();
  }
}