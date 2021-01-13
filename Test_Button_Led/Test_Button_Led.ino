#define Led 3
#define Button 4

void setup() {
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
}

void loop() {
  int sensorVal = digitalRead(Button);
  Serial.println(sensorVal);
  if (sensorVal == HIGH) {
    digitalWrite(Led, LOW);
  } else {
    digitalWrite(Led, HIGH);
  }
}
