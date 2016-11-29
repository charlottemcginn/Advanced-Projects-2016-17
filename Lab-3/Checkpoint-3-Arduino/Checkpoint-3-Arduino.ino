// Arduino Airmouse Code

#define right 6
#define left 7
#define battery 2

// Radio Pipe Stuff
byte addresses[][6] = {"One","Two"};
#include <nRF24L01.h>
#include <printf.h>d
#include <RF24.h>
#include <RF24_config.h>
uint8_t readingPipe = 1;
uint8_t writingPipe = 0;
void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel);

RF24 radio(4, 3);

// Stuct to send
struct package
{
  char color;
  char button;
};

// Setup
void setup() {

  // Initialize the buttons
  pinMode(right, INPUT);
  pinMode(left, INPUT);

  // Battery
  pinMode(battery, INPUT);

  // Start the Serial
  printf_begin();
  Serial.begin(9600);

  // Initialize the Radio
  radio_init(radio, 0, 2, 17);
}

void loop() {
 if(digitalRead(right))
 {
  package message;
  message.button = 'r';
  message.color = package_color();

  // Send r's until button is released
  do{
    
  radio.write(&message, sizeof(message));
  
  } while(digitalRead(right));

  message.button = 'n';
  radio.write(&message, sizeof(message));
 }

 if(digitalRead(left))
 {
  package message;
  message.button = 'l';
  message.color = package_color();

  // Send l's until button is released
  do{
  radio.write(&message, sizeof(message));
  } while(digitalRead(left));
  
  message.button = 'n';
  radio.write(&message, sizeof(message));
 }

}


