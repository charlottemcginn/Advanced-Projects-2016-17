void radio_init(RF24 m_radio, uint8_t power, uint8_t payload, uint8_t channel)
{
    radio.begin();
    radio.setPALevel(power);       //power min
    radio.setPayloadSize(payload); 
    radio.setChannel(channel);
    radio.setCRCLength(RF24_CRC_16);
    radio.setDataRate(RF24_1MBPS);
    radio.setAutoAck(readingPipe, true);
    radio.setAutoAck(writingPipe, true);
    radio.stopListening();
    radio.openReadingPipe(readingPipe,addresses[1]);
    radio.openWritingPipe(addresses[0]); 
    radio.startListening();
    radio.printDetails();
    Serial.println("Done initializing");
}

double voltage_detect()
{
 return(3.28*((analogRead(battery)/1023.0)/(0.7912)));
}

char package_color()
{
  double voltage = voltage_detect();
  //Serial.print("Voltage:");
  //Serial.println(voltage);
  if (voltage < 3.7)
  {
    return 'r';
  }

  else if (voltage < 3.9)
  {
    return 'y';
  }

  else
    return 'g';
}

void setSleep(bool enable)
{
  Serial.println("Starting to Sleep");
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x6B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPUAddr, 1, true);
  uint8_t power = Wire.read();
  power = (enable) ? (power | 0b01000000) : (power & 0b10111111);
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x6B);
  Wire.write(power);
  Wire.endTransmission(true);
  Serial.println("Finishing Sleep");
}

void setAccelPrec(uint8_t prec)
{
  
  prec &= 0b11100011;
  prec = prec<<3;
  
 Wire.beginTransmission(MPUAddr);
 Wire.write(0x1C);
 Wire.write(prec);
 Wire.endTransmission(true); 
}

void setGyroPrec(uint8_t prec)
{
   prec &= 0b11;
  prec = prec<<3;
  Wire.beginTransmission(MPUAddr);
  Wire.write(0x1B);
  Wire.write(prec);
  Wire.endTransmission(true);
}

void getAccelData( int16_t* ax,int16_t* ay, int16_t* az)
{
   getAccelX(ax);
   getAccelY(ay);
   getAccelZ(az);
    
}

void getAccelX(int16_t* x)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *x = Wire.read()<<8 | Wire.read();
}
void getAccelY(int16_t* y)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x3D);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *y = Wire.read()<<8 | Wire.read();
}
void getAccelZ(int16_t* z)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x3F);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *z = Wire.read()<<8 | Wire.read();
}

void getGyroData( int16_t* ax,int16_t* ay, int16_t* az)
{
   getGyroX(ax);
   getGyroY(ay);
   getGyroZ(az);
    
}

void getGyroX(int16_t* x)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *x = Wire.read()<<8 | Wire.read();
}
void getGyroY(int16_t* y)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x45);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *y = Wire.read()<<8 | Wire.read();
}
void getGyroZ(int16_t* z)
{
    Wire.beginTransmission(MPUAddr);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(MPUAddr, 2, true);
    *z = Wire.read()<<8 | Wire.read();
}
