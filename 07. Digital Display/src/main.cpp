#include <Arduino.h>
#include <TM1637Display.h>

const int displayClockPin = 8;                   // Пин CLK дисплея
const int displayDataPin = 9;                    // Пин DIO дисплея
const int firstDigit = 0;                         // Первая цифра для показа
const int lastDigit = 9;                          // Последняя цифра для показа
const int repeatedDigitMultiplier = 1111;         // Повторяет одну цифру во всех разрядах
const unsigned long displayInterval = 1000;       // 1 секунда в миллисекундах

// Класс-адаптер для четырёхразрядного дисплея TM1637
class DigitalDisplay {
private:
    TM1637Display display;

public:
    // Запоминает пины дисплея и устанавливает среднюю яркость
    DigitalDisplay(int clockPin, int dataPin) : display(clockPin, dataPin) {
        display.setBrightness(4);
    }

    // Показывает одну цифру сразу во всех четырёх разрядах
    void showNumber(int number) {
        // TODO: показать цифру во всех разрядах
    }
};

DigitalDisplay digitalDisplay(displayClockPin, displayDataPin);
int currentDigit = firstDigit;  // Цифра, которую покажем сейчас

void setup() {
    // Всё готово в конструкторе класса DigitalDisplay.
}

void loop() {
    // TODO: показать currentDigit на дисплее
    // TODO: подождать displayInterval
    // TODO: увеличить currentDigit на 1
    // TODO: если currentDigit больше lastDigit, снова сделать её равной firstDigit
}
