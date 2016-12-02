#include <Wire.h>
#define MPUAddr 0x68
#define right 7
#define left 8
#define battery 15
#include <nRF24L01.h>
#include <printf.h>d
#include <RF24.h>
#include <RF24_config.h>
uint8_t readingPipe = 1;
uint8_t writingPipe = 0;

byte addresses[][6] = {"One","Two"};
RF24 radio(3, 4);

typedef enum : uint8_t
{
  GYRO_PREC_250 = 0,
  GYRO_PREC_500 = 1,
  GYRO_PREC_1000 = 2,
  GYRO_PREC_2000 = 3
} gyro_precision_e;

typedef enum : uint8_t
{
  ACCEL_PREC_2 = 0,
  ACCEL_PREC_4 = 1,
  ACCEL_PREC_8 = 2,
  ACCEL_PREC_16 =3
} accel_precision_e;

struct package
{
  int16_t ax;
  int16_t ay;
 int16_t az;
 char color;
 char button;
}accel_data;

void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel);
void setSleep(bool enable);
void getAccelData(int16_t* ax,int16_t* ay, int16_t* az);
void getGyroData(int16_t* gx,int16_t* gy, int16_t* gz);
void setGyroPrec(uint8_t prec);
void setAccelPrec(uint8_t prec);


void setup() {
  // put your setup code here, to run once:
   // Initialize the buttons
  pinMode(right, INPUT);
  pinMode(left, INPUT);

  // Battery
  pinMode(battery, INPUT);

  // Start the Serial
  printf_begin();
  Serial.begin(9600);

  // Initialize the Radio
  radio_init(radio, 0, 8, 17);

  // Start Wire
  Serial.println("Starting Wire");
  Wire.begin();
  setAccelPrec(ACCEL_PREC_2);
  setSleep(false);
  accel_data.color = 'n';
  accel_data.button = 'n';
}

void loop() {
  delay(20);
  // put your main code here, to run repeatedly:
  //Serial.println("Getting Data");
accel_data.color = package_color();
getAccelData(&accel_data.ax, &accel_data.ay, &accel_data.az);

radio.stopListening();
radio.write((char*) &accel_data, sizeof(accel_data));
radio.startListening();

 if(digitalRead(right))
 {
  accel_data.button = 'r';
  Serial.println("Right Writing To Radio");

  radio.stopListening();
  radio.write((char*)&accel_data, sizeof(accel_data));
  radio.startListening();
 
 }
 else if(digitalRead(left))
 {
  accel_data.button = 'l';
  Serial.println("Left Writing to Radio");
  radio.stopListening();
  radio.write((char*)&accel_data, sizeof(accel_data));
  radio.startListening();

 else
 {
    accel_data.button = 'n';
 }

 Serial.println("End Loop");
}


