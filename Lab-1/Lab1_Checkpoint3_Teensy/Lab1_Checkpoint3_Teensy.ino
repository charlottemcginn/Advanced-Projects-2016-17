#define LED_R  12
#define LED_Y  11
#define LED_G  10

bool R_stat = false;
bool Y_stat = false;
bool G_stat = false;
char input_byte;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_R, R_stat);
  digitalWrite(LED_Y, Y_stat);
  digitalWrite(LED_G, G_stat);
  
}

void loop() {
  if(Serial1.available() > 0)
  {
    input_byte = Serial1.read();
    Serial.println(input_byte);

    if (input_byte == 'r')
    {
      R_stat = true;
      digitalWrite(LED_R, R_stat);
      //delay(500);
      while(input_byte != 'n')
      {
        input_byte = Serial1.read();
        delay(10);
      }
      R_stat = false;
      digitalWrite(LED_R, R_stat);
      //delay(500);
    }

    if (input_byte == 'y')
    {
      Y_stat = true;
      digitalWrite(LED_Y, Y_stat);
      //delay(500);
      while(input_byte != 'n')
      {
        input_byte = Serial1.read();
        delay(10);
      }
      Y_stat = false;
      digitalWrite(LED_Y, Y_stat);
      //delay(500);
    }

    if (input_byte == 'g')
    {
      G_stat = true;
      digitalWrite(LED_G, G_stat);
      //delay(500);
      while(input_byte != 'n')
      {
        input_byte = Serial1.read();
        delay(10);
      }
      G_stat = false;
      digitalWrite(LED_G, G_stat);
      //delay(500);
    }
  
  }
}
