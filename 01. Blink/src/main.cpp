#include <Arduino.h>

const int ledPin = 5;

void turnLedOn() {
    digitalWrite(ledPin, HIGH);
}

void turnLedOff() {
    digitalWrite(ledPin, LOW);
}

void setup() {
    pinMode(ledPin, OUTPUT);
}

void loop() {
    turnLedOn();
    delay(500);
    turnLedOff();
    delay(1000);
}
