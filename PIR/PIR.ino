#define PIR 4

void setup() 
{
  pinMode(PIR, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.println(digitalRead(PIR));
  delay(500);
}
