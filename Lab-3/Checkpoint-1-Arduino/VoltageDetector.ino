double batteryV;
void setup() {
  Serial.begin(9600);
  pinMode(15, INPUT);

}

void loop() {
  batteryV = 3.28*((analogRead(15)/1023.0)/(0.8187));
  delay(100);
  Serial.println(batteryV);
}
