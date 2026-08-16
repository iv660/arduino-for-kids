#include <Arduino.h>

const int buttonPin = 6;
const int ledPin = 5;

// Переменная для отслеживания состояния светодиода
bool lightState = false;

// Переменная для отслеживания состояния кнопки в предыдущем цикле (для Этапа 2)
bool lastButtonState = HIGH;

// ЭТАП 3: Мигающий светодиод с выключателем

bool isBlinking = false;  // Включено ли мигание?
unsigned long lastBlinkTime = 0;  // Когда светодиод последний раз переключался?
const unsigned long blinkInterval = 500;  // Интервал мигания в миллисекундах

// ЭТАП 1: Простое управление (светодиод включен, пока нажата кнопка)

// Возвращает true, если кнопка нажата
bool buttonIsDown() {
    return digitalRead(buttonPin) == LOW;
}

// Возвращает true, если кнопка отпущена
bool buttonIsUp() {
    return digitalRead(buttonPin) == HIGH;
}

// Включает светодиод
void turnLightOn() {
    digitalWrite(ledPin, HIGH);
    lightState = true;
}

// Выключает светодиод
void turnLightOff() {
    digitalWrite(ledPin, LOW);
    lightState = false;
}

// Возвращает true, если светодиод горит
bool lightIsOn() {
    return lightState == true;
}

// Возвращает true, если светодиод не горит
bool lightIsOff() {
    return lightState == false;
}

// ЭТАП 2: Выключатель (toggle - светодиод переключается при каждом нажатии)

// Возвращает true только один раз — когда кнопка только что была нажата
bool buttonWasPressed() {
    bool currentButtonState = digitalRead(buttonPin);

    if (currentButtonState == LOW && lastButtonState == HIGH) {
        lastButtonState = currentButtonState;
        return true;
    }

    lastButtonState = currentButtonState;
    return false;
}

// Переключает светодиод: если был включён — выключи, если выключен — включи
void toggleLight() {
    if (lightIsOn()) {
        turnLightOff();
    } else {
        turnLightOn();
    }
}

// ЭТАП 3: Мигающий светодиод с выключателем

// Сбрасывает счётчик времени мигания
void resetBlinkInterval() {
    lastBlinkTime = millis();
}

// Переключает режим мигания
void toggleBlinking() {
    if (isBlinking) {
        isBlinking = false;
        turnLightOff();
    } else {
        resetBlinkInterval();
        isBlinking = true;
        turnLightOn();
    }
}

// Возвращает true, если прошло достаточно времени для переключения светодиода
bool blinkIntervalElapsed() {
    return millis() - lastBlinkTime >= blinkInterval;
}

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    if (buttonWasPressed()) {
        toggleBlinking();
    }

    if (isBlinking && blinkIntervalElapsed()) {
        toggleLight();
        resetBlinkInterval();
    }
}
