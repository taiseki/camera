#include "DS3235.h"
#include <M5Stack.h>

int prevch;

void DS3235::begin(int pin, int ch) {
    _ch = ch;
    ledcSetup(_ch, 50, 10);
    ledcAttachPin(pin, _ch);
    DS3235::write(0);
}

void DS3235::write(int angle) {
    if (prevch != _ch) {
        delay(50);
    }
    prevch = _ch;
    ledcWrite(_ch, map(constrain(angle, 0, 180), 0, 180, _min, _max));
    _angle = constrain(angle, 0, 180);
    Serial.printf("%d: %d\r\n", _ch, _angle);
}

void DS3235::plus(void) {
    DS3235::write(_angle + 10);
}

void DS3235::minus(void) {
    DS3235::write(_angle - 10);
}
