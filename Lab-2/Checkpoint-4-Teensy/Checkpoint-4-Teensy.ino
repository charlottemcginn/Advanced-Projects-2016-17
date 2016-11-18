
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#define yellow 5
#define green 2
#define red 7

uint8_t readingPipe = 1;
uint8_t writingPipe = 0;
void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel);
byte addresses[][6] = {"Two", "One"};
bool sent = false;
int num = 5;

char seq[20];
char c[3] = {'r','g','y'};
int r = 0;
bool gameover = false;
bool sending = true;


//Stuct to send
struct package
{
  char color;
};

package message;
package send_s;
RF24 radio(9, 14);

// Setup
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  while(!Serial);
  // put your setup code here, to run once:
  printf_begin();
  radio_init(radio, 0, 1, 17);
   randomSeed(analogRead(0));
  for(int i =0; i < 20; i++)
  {
    randomChar(i);
  }
           radio.stopListening();
  radio.write((char*) &send_s, sizeof(send_s));
  radio.startListening();
  Serial.print("Sent the character: ");
  
        Serial.println(send_s.color);
}

// Radio initialize function
void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel)
{
  Serial.println("Initializing Radio");
  radio.begin();
  radio.setPALevel(power);       //power min
  radio.setPayloadSize(payload); // payload 32 bytes
  radio.setChannel(channel);
  radio.setCRCLength(RF24_CRC_16);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(readingPipe, true);
  radio.setAutoAck(writingPipe, true);
  radio.stopListening();
  radio.openReadingPipe(readingPipe, addresses[1]);
  radio.openWritingPipe(addresses[0]);
  radio.startListening();
  Serial.println("Done initializing");
  
  message.color = ' ';
  send_s.color = 's';
}
void loop() {
  // Initialize the struct
  //radio.printDetails();
  package currentColor;
  currentColor.color = seq[r];
    if(!gameover)
  {
    
    if(sending)
    {  
      if(r<20)
      {
        delay(300);
        playSequence();
        radio.stopListening();
        radio.write((char*) &currentColor, sizeof(currentColor));
        Serial.print("Sent the character: ");
        Serial.println(currentColor.color);
        radio.startListening();
        r++;
      }
      
      sending = false;
    }
    if(!sending)
    {
      while(!radio.available());
       radio.read(&message, sizeof(message));
       Serial.print("Read the character: ");
        Serial.println(message.color);
       if(message.color == 'y')
       {
          delay(500);
          playWin();
          delay(600);
          Serial.println("Sent");
          sending = true;
          message.color = ' ';
       }
       else if(message.color == 'n')
       {
          Serial.println("Nope");
          playLose();
          //gameover = true;
          sending = true;
          r = 0;
          delay(400);
          radio.stopListening();
          radio.write((char*) &send_s, sizeof(send_s));
          radio.startListening();
          Serial.print("Sent the character: ");
        Serial.println(send_s.color);
          for(int i =0; i < 20; i++)
          {
          randomChar(i);
          }
          message.color = ' ';
       }
       
    }
  }
} 

  void randomChar(int pos)
{
  seq[pos] = c[random(3)];
}

void playSequence()
{
  for(int i = 0; i <= r; i++)
  {
    lightLED(seq[i]);
  }
}

void playLose()
{
  for(int i = 0; i < 5; i++)
  {
  digitalWrite(red, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(green, HIGH);
  delay(500);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(500);
  }
}

void playWin()
{
  for(int i = 0; i < 4; i++)
  {
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(100);
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  delay(100);
  digitalWrite(green, LOW);
  }
}

void lightLED(char a)
{
  if(a=='r')
  {
    digitalWrite(red, HIGH);
  }
  if(a=='g')
  {
    digitalWrite(green, HIGH);
  }
  if(a=='y')
  {
    digitalWrite(yellow, HIGH);
  }
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(300);
}



