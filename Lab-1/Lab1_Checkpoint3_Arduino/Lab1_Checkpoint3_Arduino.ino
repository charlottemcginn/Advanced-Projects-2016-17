#define BUTTON_R 7
#define BUTTON_Y 8
#define BUTTON_G 9
#include <SoftwareSerial.h>

SoftwareSerial sendingSerial(3,2);

void setup() {
  Serial.begin(9600);
  sendingSerial.begin(9600);
  pinMode(BUTTON_R, INPUT);
  pinMode(BUTTON_Y, INPUT);
  pinMode(BUTTON_G, INPUT);
  Serial.print("beginning loop");
}

void loop() {
  if(digitalRead(BUTTON_R))
  {
    Serial.write('r');
    sendingSerial.write('r');
    while(digitalRead(BUTTON_R))
    {
      delay(10);
    }
    sendingSerial.write('n');
  }
  
  if(digitalRead(BUTTON_Y))
  {
    Serial.write('y');
    sendingSerial.write('y');
    while(digitalRead(BUTTON_Y))
    {
      delay(10);
    }
    sendingSerial.write('n');
  }
  
  if(digitalRead(BUTTON_G))
  {
    Serial.write('g');
    sendingSerial.write('g');
    while(digitalRead(BUTTON_G))
    {
      delay(10);
    }
    sendingSerial.write('n');
  }

}
