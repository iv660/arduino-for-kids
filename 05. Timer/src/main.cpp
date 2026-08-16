#include <Arduino.h>

const int relayPin = 7;                         // Пин первого реле шилда
const int buttonPin = 3;                        // Пин кнопки запуска
const unsigned long timerInterval = 10000;      // 10 секунд в миллисекундах

// Класс из урока 04 для управления одним реле
class Relay {
private:
    int pin;  // Пин, который управляет реле

public:
    // Запоминает пин и сразу выключает реле
    Relay(int relayPin) {
        pin = relayPin;
        pinMode(pin, OUTPUT);
        off();
    }

    // Включает реле. У этого шилда HIGH означает «включить».
    void on() {
        digitalWrite(pin, HIGH);
    }

    // Выключает реле. У этого шилда LOW означает «выключить».
    void off() {
        digitalWrite(pin, LOW);
    }
};

// Класс для кнопки, которая замечает новое нажатие
class Button {
private:
    int pin;                 // Пин, к которому подключена кнопка
    bool previousState;      // Состояние кнопки при прошлой проверке

public:
    // Запоминает пин и готовит его для кнопки
    Button(int buttonPin) {
        pin = buttonPin;
        pinMode(pin, INPUT_PULLUP);
        previousState = HIGH;
    }

    // Возвращает true только один раз при новом нажатии кнопки
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

// Класс для отсчёта заданного промежутка времени
class Timer {
private:
    unsigned long interval;  // Сколько должен длиться отсчёт
    unsigned long startTime; // Когда отсчёт начался
    bool started;            // Был ли таймер запущен хотя бы раз

public:
    // Запоминает длительность отсчёта
    Timer(unsigned long timerInterval) {
        interval = timerInterval;
        startTime = 0;
        started = false;
    }

    // Запускает таймер заново с самого начала
    void restart() {
        startTime = millis();
        started = true;
    }

    // Останавливает таймер, чтобы его можно было запустить снова
    void stop() {
        started = false;
    }

    // Возвращает true, пока отсчёт ещё продолжается
    bool isRunning() {
        if (!started) {
            return false;
        }

        if (isFinished()) {
            return false;
        }

        return true;
    }

    // Возвращает true, если запущенный таймер уже закончился
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

Relay relay(relayPin);
Button button(buttonPin);
Timer timer(timerInterval);

void setup() {
    // Всё готово в конструкторах классов.
}

void loop() {
    if (timer.isRunning()) { // Если таймер работает:
        return; // - ничего не делаем, сразу вызываем return
    }

    if (timer.isFinished()) { // Если таймер завершён:
        relay.off(); // - выключаем реле
        timer.stop(); // - останавливаем таймер
        return; // - вызываем return
    }

    if (button.wasPressed()) { // Если кнопка нажата:
        relay.on(); // - включаем реле
        timer.restart(); // - перезапускаем таймер
        return; // - вызываем return
    }
}
