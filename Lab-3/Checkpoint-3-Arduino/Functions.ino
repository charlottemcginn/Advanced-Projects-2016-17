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
    Serial.println("Done initializing");
}

char voltage_detect()
{
 return(3.28*((analogRead(15)/1023.0)/(0.8187)));
}

char package_color()
{
  double voltage = voltage_detect();
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

