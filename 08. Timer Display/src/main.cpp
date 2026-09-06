#include <Arduino.h>
#include <TM1637Display.h>

const int relayPin = 7;                          // Пин первого реле шилда
const int buttonPin = 3;                         // Пин кнопки запуска
const int potentiometerPin = A0;                 // Пин ползунка потенциометра
const int displayClockPin = 8;                   // Пин CLK дисплея
const int displayDataPin = 9;                    // Пин DIO дисплея
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

    // Возвращает оставшееся время в миллисекундах
    unsigned long getRemainingTime() {
        // TODO: реализуй метод getRemainingTime
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

// Класс для отображения времени на четырёхразрядном дисплее TM1637
class TimeDisplay {
private:
    TM1637Display display;
    const uint8_t colonBit = 0b01000000;  // Бит для включения двоеточия

public:
    TimeDisplay(int clockPin, int dataPin) : display(clockPin, dataPin) {
        display.setBrightness(4);
    }

    // Устанавливает минуты в левых двух разрядах
    void setMinutes(int minutes) {
        // TODO: реализуй метод setMinutes
    }

    // Устанавливает секунды в правых двух разрядах
    void setSeconds(int seconds) {
        // TODO: реализуй метод setSeconds
    }
};

// Класс для отображения времени в минутах и секундах
class TimeView {
private:
    unsigned long timeInMilliseconds;
    TimeDisplay* display;

    // Возвращает количество минут из сохранённого времени
    int getMinutes() {
        // TODO: реализуй метод getMinutes
    }

    // Возвращает количество секунд из сохранённого времени
    int getSeconds() {
        // TODO: реализуй метод getSeconds
    }

    // Обновляет информацию на дисплее
    void updateDisplay() {
        // TODO: реализуй метод updateDisplay
    }

public:
    TimeView(TimeDisplay* timeDisplay) {
        display = timeDisplay;
        timeInMilliseconds = 0;
    }

    // Устанавливает время для отображения и обновляет дисплей
    void setTimeInMilliseconds(unsigned long time) {
        // TODO: реализуй метод setTimeInMilliseconds
    }
};

Relay relay(relayPin);
Button button(buttonPin);
Timer timer(0);
Potentiometer potentiometer(potentiometerPin, minimumIntervalSeconds, maximumIntervalSeconds);
TimeDisplay timeDisplay(displayClockPin, displayDataPin);
TimeView timeView(&timeDisplay);

void setup() {
    // Всё готово в конструкторах классов.
}

void loop() {
    if (timer.isRunning()) {
        // TODO: получи оставшееся время методом timer.getRemainingTime()
        // TODO: передай это время в timeView.setTimeInMilliseconds()
        return;
    }
    
    if (timer.isFinished()) {
        relay.off();
        timer.stop();
        // TODO: получи выбранный интервал потенциометром
        // TODO: переведи секунды в миллисекунды
        // TODO: покажи интервал на дисплее через timeView.setTimeInMilliseconds()
        return;
    }

    if (button.wasPressed()) {
        int intervalInSeconds = potentiometer.getPosition();
        unsigned long intervalInMilliseconds = intervalInSeconds * millisecondsInSecond;
        timer.setInterval(intervalInMilliseconds);

        relay.on();
        timer.restart();
        return;
    }
}
