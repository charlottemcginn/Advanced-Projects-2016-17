// Teensy Airmouse Code

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#define yellow 5
#define green 2
#define red 7

int nX;
int nY;
int nZ;

char prevbutt = 'n';
int nXprev = 0;
int nYprev = 0;

// Stuct to send
struct package
{
  int16_t Ax; 
  int16_t Ay;
  int16_t Az;
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
  radio_init(radio, 2, 8, 17);
  radio.startListening();
}

void loop() {

  // Wait while the radio is not available
  while(!radio.available());

  // Read in struct and print out input
  radio.read((char*) &message, sizeof(message));
  nX = message.Ay + 100;
  nY = message.Ax - 520;
  nZ = message.Az - 7600;
  /*
  Serial.print("Read the characters: ");
  Serial.print(message.color);
  Serial.print(", ");
  Serial.print("X: ");
  Serial.print(nX);
  Serial.print(", Y: ");
  Serial.print(nY);
  Serial.print(", Z: ");
  Serial.println(nZ);
*/
  if (abs(nXprev - nX) > 100 || abs(nYprev - nY) > 100)
     Mouse.move(-nX*0.004, nY*0.004);
  

  // Light the corresponding LED color
 lightLED(message.color);

  // Continue to print the button press
  // As long as the button is held down
  //delay(100);
 if (message.buttons != 'n')
 {
  if (message.buttons == 'r' && message.buttons != prevbutt)
  {
        Serial.print("r");
        Mouse.set_buttons(1, 0, 0);
        prevbutt = 'r';
  }
    
  if (message.buttons == 'l' && message.buttons != prevbutt)
  {
        Serial.print("l");
        Mouse.set_buttons(0, 0, 1);
        prevbutt = 'l';
  }
 }
  else if (message.buttons == 'n')
  {
    Mouse.set_buttons(0,0,0);
    prevbutt = 'n';
  }
  Serial.println();
  //LEDSoff();

  nXprev = nX;
  nYprev = nY;
} 







