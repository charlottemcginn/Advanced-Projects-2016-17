//Sending
#define red 9
#define yellow 8
#define green 7
#include <SoftwareSerial.h>
int roundnumber = 0;
int playnumber = 0;
bool play = false;
 char sequence[20];
 char start;
 char current;
 bool s = false;
 
SoftwareSerial ProCereal(3,2); // 3 RX (RECIEVE) 2 TX (SEND)
void setup() {
  pinMode(red, INPUT);
  pinMode(yellow, INPUT);
  pinMode(green, INPUT);
  Serial.begin(9600);
  ProCereal.begin(9600);
  Serial.println("begin");
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
    Serial.println("r");
   }
   else if(digitalRead(green))
   {
    current = 'g';
    Serial.println("g");
   }
   else if(digitalRead(yellow))
   {
    current = 'y';
    Serial.println("y");
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
      Serial.println("y");
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
      Serial.println("n");
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


