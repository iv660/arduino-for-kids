#include <Arduino.h>

// Пины для компонентов
const int ledPin = 3;              // Пин светодиода (PWM)
const int potentiometerPin = A0;   // Пин переменного резистора (аналоговый вход)

// Класс для управления переменным резистором
class Potentiometer {
private:
    int pin;
    int minValue;
    int maxValue;

public:
    // Конструктор - задаём пин и диапазон значений при создании объекта
    Potentiometer(int potPin, int minVal, int maxVal) {
        pin = potPin;
        minValue = minVal;
        maxValue = maxVal;
        pinMode(pin, INPUT);
    }

    // Получить текущее положение ползунка, переведённое в диапазон от minValue до maxValue
    int getPosition() {
        int rawValue = analogRead(pin);
        int scaledValue = map(rawValue, 0, 1023, minValue, maxValue);
        return scaledValue;
    }
};

// Класс для управления светодиодом с регулируемой яркостью
class DimmableLed {
private:
    int pin;
    int currentBrightness;

public:
    // Конструктор - задаём пин при создании объекта
    DimmableLed(int ledPin) {
        pin = ledPin;
        currentBrightness = 0;
        pinMode(pin, OUTPUT);
        void on() {
            setBrightness(255);
        }
        void off() {
            setBrghtness(0);
        }
    }

    // Установить яркость (0-255)
    void setBrightness(int brightness) {
        currentBrightness = brightness;
        analogWrite(pin, brightness);
    }
};

// Создаём объекты: светодиод и ползунок
DimmableLed led(ledPin);
Potentiometer pot = Potentiometer(potentiometerPin, 1, 255);

void setup() {
    // Всё готово в конструкторах классов
}

void loop() {
    int brightness = pot.getPosition();
    led.setBrightness(brightness);
}
