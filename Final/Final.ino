#include <EEPROM.h>

#define Button 2
#define Led 3
#define LedPower 4
#define Relay 9
#define Pir 10

byte delayArray[3] = {5, 10, 15};
byte delayChoice = EEPROM.read(0);
byte delayChoiceBlink = EEPROM.read(0);

void adjustDelayTime() {
    if (!digitalRead(Button)) {
        delay(20);
        if (!digitalRead(Button)) {
            if (delayChoice < 2) {
                delayChoice++;
                EEPROM.update(0, delayChoice);
            } else {
                delayChoice = 0;
                EEPROM.update(0, delayChoice);
            }
            while (!digitalRead(Button)) {
            }
        }
    }
}

void setup() {
    pinMode(Button, INPUT_PULLUP);
    pinMode(Led, OUTPUT);
    pinMode(LedPower, OUTPUT);
    digitalWrite(LedPower, HIGH);
    pinMode(Relay, OUTPUT);
    pinMode(Pir, INPUT);
    attachInterrupt(0, adjustDelayTime, FALLING);
}

void blinkLed() {
    if (delayChoiceBlink != delayChoice) {
        delayChoiceBlink = delayChoice;
        for (int i = 0; i <= delayChoice; i++) {
            digitalWrite(Led, HIGH);
            delay(200);
            digitalWrite(Led, LOW);
            delay(200);
        }
    }
}

void delayPir(int delayValue) {
    for (int i = 0; i < (5 * delayValue); i++) {
        blinkLed();
        delay(200);
        if (digitalRead(Pir)) {
            i = 0;
        }
    }
}

void delayPirNoRepeat(int delayValue) {
    for (int i = 0; i < (5 * delayValue); i++) {
        blinkLed();
        delay(200);
    }
}

void loop() {
    blinkLed();
    if (digitalRead(Pir)) {
        delay(200);
        if (digitalRead(Pir)) {
            digitalWrite(Relay, HIGH);
            while (digitalRead(Pir)) {
                blinkLed();
            }
            delayPirNoRepeat(3);
            delayPir(delayArray[delayChoice]);
            digitalWrite(Relay, LOW);
        }
    }
}
