#include <EEPROM.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

void setup()
{
  pinMode(8,OUTPUT);//I-P1
  pinMode(9,OUTPUT);//I-N1
  pinMode(12,OUTPUT);//I-P2
  pinMode(13,OUTPUT);//I-N2
  
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[3]; //buf[0]-L buf[1]-R buf[2]-s or motion(if s=0 car will stop else in motion)
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);  
      if(buf[2]=='0'){
          digitalWrite(8,LOW);
          digitalWrite(9,LOW);
          digitalWrite(12,LOW);
          digitalWrite(13,LOW);
      }
      else{
          if(buf[0]=='1' && buf[1]=='1'){
            digitalWrite(8,HIGH);
            digitalWrite(9,LOW);
            digitalWrite(12,HIGH);
            digitalWrite(13,LOW);
          }
          if(buf[0]=='1' && buf[1]=='0'){
            digitalWrite(8,HIGH);
            digitalWrite(9,LOW);
            digitalWrite(12,LOW);
            digitalWrite(13,HIGH);
          }
          if(buf[0]=='0' && buf[1]=='1'){
            digitalWrite(8,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(12,HIGH);
            digitalWrite(13,LOW);
          }
          if(buf[0]=='0' && buf[1]=='0'){
            digitalWrite(8,LOW);
            digitalWrite(9,HIGH);
            digitalWrite(12,LOW);
            digitalWrite(13,HIGH);
          }
      }
    }
}
