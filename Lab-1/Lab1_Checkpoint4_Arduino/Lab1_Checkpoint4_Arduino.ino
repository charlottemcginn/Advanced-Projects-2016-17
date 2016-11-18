//Sending
#define red 14
#define yellow 15
#define green 16
#include <SoftwareSerial.h>
int roundnumber = 0;
int playnumber = 0;
bool play = false;
 char sequence[20];
 char start;
 char current;
 bool s = false;
 
SoftwareSerial ProCereal(4,5); // 4 RX (RECIEVE) 5 TX (SEND)
void setup() {
  Serial.begin(9600);
  ProCereal.begin(9600);
 
}

void loop() {
 if(s == false)
    start = ProCereal.read();

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
    //ProCereal.write('y');
    //play = false;
    if(current == sequence[playnumber])
    {
      if(playnumber == (roundnumber-1))
      {
      ProCereal.write('y');
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
      ProCereal.write('n');
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
   s = true;
   char color;
   color = ProCereal.read();

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


