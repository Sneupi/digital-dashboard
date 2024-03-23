#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <Arduino.h>

class PushButton {
private:
    int pb_pin;
    int pbLast = LOW;
    int pbCurrent;
    void (*registeredFunction)();

public:
    PushButton(int pb) {
        pb_pin = pb;
        pinMode(pb_pin, INPUT_PULLUP);
    }

    void registerFunction(void (*function)()) {
        registeredFunction = function;
    }

    void checkState() {
        pbCurrent = digitalRead(pb_pin);
        if (pbLast == HIGH && pbCurrent == LOW) {
            if (registeredFunction != nullptr) {
                registeredFunction();
            }
        }
        pbLast = pbCurrent;
    }
};

#endif // PUSHBUTTON_H