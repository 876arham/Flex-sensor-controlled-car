#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[3];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);  
      if(buf[0]=='1')
        digitalWrite(2,HIGH);
       else
        digitalWrite(2,LOW);
      if(buf[1]=='1')
        digitalWrite(3,HIGH);
      else
        digitalWrite(3,LOW);
      if(buf[2]=='1')
        digitalWrite(4,HIGH);
      else
        digitalWrite(4,LOW);
    }
}
