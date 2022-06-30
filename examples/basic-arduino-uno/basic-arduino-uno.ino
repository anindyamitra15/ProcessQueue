/**
 * @file main.cpp
 * @author Anindya Kanti Mitra (@anindyamitra15)
 * @brief Simple demonstration which shows the application
 * of ProcessQueue.
 * The program uses an external (Falling edge triggered) interrupt
 * to push a function to the queue which is then handled
 * automatically by the loop() of the ProcessQueue
 *
 * @version 1.0
 * @date 2022-07-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <ProcessQueue.h>

ProcessQueue p_queue;

// actual event to be triggered by the ISR
void_function event = []()
{
  Serial.println("Event Triggered");
  delay(3000);
  Serial.println("Event Serviced");
};

void ISR_func()
{
  // ISR just pushes the event to the queue
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
}
