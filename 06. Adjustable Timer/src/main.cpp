#include <Arduino.h>

const int relayPin = 7;                          // Пин первого реле шилда
const int buttonPin = 3;                         // Пин кнопки запуска
const int potentiometerPin = A0;                 // Пин ползунка потенциометра
const int minimumIntervalSeconds = 5;            // Самый короткий интервал
const int maximumIntervalSeconds = 120;          // Самый длинный интервал
const unsigned long millisecondsInSecond = 1000; // Сколько миллисекунд в секунде

// Класс из урока 04 для управления одним реле
class Relay {
private:
    int pin;

public:
    Relay(int relayPin) {
        pin = relayPin;
        pinMode(pin, OUTPUT);
        off();
    }

    void on() {
        digitalWrite(pin, HIGH);
    }

    void off() {
        digitalWrite(pin, LOW);
    }
};

// Класс из урока 05 для кнопки, которая замечает новое нажатие
class Button {
private:
    int pin;
    bool previousState;

public:
    Button(int buttonPin) {
        pin = buttonPin;
        pinMode(pin, INPUT_PULLUP);
        previousState = HIGH;
    }

    bool wasPressed() {
        bool currentState = digitalRead(pin);

        if (currentState != LOW) {
            previousState = currentState;
            return false;
        }

        if (previousState != HIGH) {
            previousState = currentState;
            return false;
        }

        previousState = currentState;
        return true;
    }
};

// Класс из урока 05 для отсчёта заданного промежутка времени
class Timer {
private:
    unsigned long interval;
    unsigned long startTime;
    bool started;

public:
    Timer(unsigned long timerInterval) {
        interval = timerInterval;
        startTime = 0;
        started = false;
    }

    // Меняет длительность следующего отсчёта
    void setInterval(unsigned long timerInterval) {
        interval = timerInterval;
    }

    void restart() {
        startTime = millis();
        started = true;
    }

    void stop() {
        started = false;
    }

    bool isRunning() {
        if (!started) {
            return false;
        }

        if (isFinished()) {
            return false;
        }

        return true;
    }

    bool isFinished() {
        if (!started) {
            return false;
        }

        if (millis() - startTime < interval) {
            return false;
        }

        return true;
    }
};

// Класс из урока 03 для управления потенциометром
class Potentiometer {
private:
    int pin;
    int minValue;
    int maxValue;

public:
    Potentiometer(int potPin, int minVal, int maxVal) {
        pin = potPin;
        minValue = minVal;
        maxValue = maxVal;
        pinMode(pin, INPUT);
    }

    int getPosition() {
        int rawValue = analogRead(pin);
        int scaledValue = map(rawValue, 0, 1023, minValue, maxValue);
        return scaledValue;
    }
};

Relay relay(relayPin);
Button button(buttonPin);
Timer timer(0);
Potentiometer potentiometer(potentiometerPin, minimumIntervalSeconds, maximumIntervalSeconds);

void setup() {
    // Всё готово в конструкторах классов.
}

void loop() {
    if (timer.isRunning()) {
        return;
    }
    
    if (timer.isFinished()) {
        relay.on();
        timer.stop();
        return;
    }

    if (button.wasPressed()) {
        int intervalInSeconds = potentiometer.getPosition();
        unsigned long intervalInMilliseconds = intervalInSeconds * millisecondsInSecond;
        timer.setInterval(intervalInMilliseconds);

        relay.off();
        timer.restart();
        return;
    }
}
