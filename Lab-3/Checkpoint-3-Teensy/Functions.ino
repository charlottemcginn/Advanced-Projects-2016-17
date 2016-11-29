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
}

void lightLED(char a)
{
  if(a=='r')
  {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  }
  if(a=='g')
  {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
  }
  if(a=='y')
  {
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
  }
  delay(100);
}

void LEDSoff()
{
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
  delay(100);
}


