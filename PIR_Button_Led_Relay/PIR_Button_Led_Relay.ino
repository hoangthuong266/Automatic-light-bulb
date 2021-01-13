#include <EEPROM.h>

#define Button 2
#define Led 3
#define Pir 4
#define Relay 5

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
    Serial.begin(9600);
    pinMode(Button, INPUT_PULLUP);
    pinMode(Led, OUTPUT);
    pinMode(Pir, INPUT);
    pinMode(Relay, OUTPUT);
    attachInterrupt(0, adjustDelayTime, FALLING);
    Serial.print("delayChoice: ");
    Serial.println(delayChoice);
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
            Serial.println("New moves detected!");
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
        Serial.println("PIR Output: 1");
        delay(200);
        if (digitalRead(Pir)) {
            Serial.println("Turn on LED bulb!");
            digitalWrite(Relay, HIGH);
            while (digitalRead(Pir)) {
                blinkLed();
            }
            Serial.println("PIR Output: 0");
            delayPirNoRepeat(3);
            delayPir(delayArray[delayChoice]);
            Serial.println("Turn off LED bulb!");
            digitalWrite(Relay, LOW);
        }
    }
}
