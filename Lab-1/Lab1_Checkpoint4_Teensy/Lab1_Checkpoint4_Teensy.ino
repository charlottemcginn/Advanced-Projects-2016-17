#define yellow 14
#define green 15
#define red 16

uint16_t randNum;
char seq[20];
char c[3] = {'r','g','y'};
int r = 0;
bool gameover = false;
bool sending = true;
char message = 'y';
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  randomSeed(analogRead(0));
  for(int i =0; i < 20; i++)
  {
    randomChar(i);
  }
  Serial1.write('s');
}

void loop() {

  if(!gameover)
  {

    if(sending)
    {  
      if(r<20)
      {
        delay(300);
        playSequence();
        Serial1.write(seq[r]);
        r++;
      }
      
      sending = false;
    }
    if(!sending)
    {
       message = Serial1.read();
       if(message == 'y')
       {
          delay(500);
          playWin();
          delay(600);
          Serial.println("Sent");
          sending = true;
          message = ' ';
       }
       else if(message == 'n')
       {
          Serial.println("Nope");
          playLose();
          //gameover = true;
          sending = true;
          r = 0;
          delay(400);
          Serial1.write('s');
          for(int i =0; i < 20; i++)
          {
          randomChar(i);
          }
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



