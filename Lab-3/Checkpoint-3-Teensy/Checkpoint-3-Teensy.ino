// Teensy Airmouse Code

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#define yellow 5
#define green 2
#define red 7

// Stuct to send
struct package
{
  char color;
  char buttons;
};

// Radio Pipe Stuff
uint8_t readingPipe = 1;
uint8_t writingPipe = 0;
void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel);
byte addresses[][6] = {"Two", "One"};
package message;

// TODO: get right pin numbers
RF24 radio(9, 14);

// Setup
void setup() {
  
  // Initialize the LEDs
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  // Start the Serial
  Serial.begin(9600);
  while(!Serial);
  
  // Initialize the Radio
  // Start listening for the airmouse
  printf_begin();
  radio_init(radio, 0, 2, 17);
  radio.startListening();
}

void loop() {

  // Wait while the radio is not available
  while(!radio.available());

  // Read in struct and print out input
  radio.read(&message, sizeof(message));
  Serial.print("Read the characters: ");
  Serial.print(message.color);
  Serial.print(", ");
  Serial.println(message.buttons);

  // Light the corresponding LED color
  lightLED(message.color);

  // Continue to print the button press
  // As long as the button is held down
  while(message.buttons != 'n')
  {
    Serial.print(message.buttons);
    radio.read(&message, sizeof(message));
  }
  Serial.println();
  LEDSoff();
} 





