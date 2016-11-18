//Sending
#define red 14
#define yellow 15
#define green 16

byte addresses[][6] = {"One","Two"};
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
uint8_t readingPipe = 1;
uint8_t writingPipe = 0;
void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel);

struct ch 
{
  char character;
} c;

int roundnumber = 0;
int playnumber = 0;
bool play = false;
char sequence[20];
char start;
char current;
bool s = false;
 
RF24 radio(5, 4);

void setup() {
  printf_begin();
  Serial.begin(9600);
  radio_init(radio, 0, 1, 17);
  radio.openReadingPipe(readingPipe,addresses[1]);
  radio.openWritingPipe(addresses[0]); 
}

void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel)
{
radio.begin();
radio.setPALevel(power);       //power min
radio.setPayloadSize(payload); // payload 32 bytes
radio.setChannel(channel);
radio.setCRCLength(RF24_CRC_16);
radio.setDataRate(RF24_1MBPS);
radio.setAutoAck(readingPipe, true);
radio.setAutoAck(writingPipe, true);
radio.startListening();
}


void loop() {
 if(s == false)
 {
    while(!radio.available());
    radio.read(&start, sizeof(start));
    
    Serial.print("one: ");
    Serial.println(start);
 }

 if(play == true && start == 's')
 {
    current = ' ';
   if(digitalRead(red))
   {
    current = 'r';
   }
   else if(digitalRead(green))
   {
    current = 'g';
   }
   else if(digitalRead(yellow))
   {
    current = 'y';
   }
   if(current == 'y' || current == 'r' || current == 'g')
   {
    if(current == sequence[playnumber])
    {
      if(playnumber == (roundnumber-1))
      {
      char y = 'y';
      radio.stopListening();
      radio.write(&y, sizeof(y));
      radio.startListening();
      playnumber = 0;
      play = false;
      }
      else
      {
        playnumber++;
        delay(300);
      }
    } else
    {
      Serial.println("Sent n");
      char n= 'n';
      radio.stopListening();
      radio.write(&n, sizeof(n));
      radio.startListening();
      roundnumber = 0;
      s = false;
      start = ' ';
      playnumber = 0;
      play = false;
    }
   }
 }
 if(start == 's' && play == false)
 {
   Serial.print("two: ");
   s = true;
   char color;
   while(!radio.available());
   radio.read(&color, sizeof(color));
   Serial.println(color);
   

   if(color == 'r' || color == 'g' || color == 'y')
   {
     sequence[roundnumber] = color;
     play = true;
     /*if(roundnumber <= 19)
     {
      Serial.println(sequence[roundnumber]);
     }*/
     //delay(100);
     roundnumber++;
   }
 }
 
}


