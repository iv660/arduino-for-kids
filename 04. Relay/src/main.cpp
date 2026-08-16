#include <Arduino.h>

const unsigned long relayInterval = 1000;      // 10 секунд в миллисекундах

// Класс для управления одним реле
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

// Первое реле шилда подключено к цифровому пину 7 Arduino
Relay relay(7);

void setup() {
    // Всё готово в конструкторе класса Relay.
}

void loop() {
    relay.on();
    delay(relayInterval);

    relay.off();
    delay(relayInterval);
}
