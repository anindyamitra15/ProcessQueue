#include <Arduino.h>
#include <ProcessQueue.h>

ProcessQueue queue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(queue.size());
  queue.push(21);
  queue.push(22);
  queue.push(23);
  Serial.println(queue.size());
  queue.pop();
  Serial.println(queue.size());
  queue.clear();
  Serial.println(queue.size());
}

void loop() {
  // put your main code here, to run repeatedly:
}