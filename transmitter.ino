//Transmitter Code (Glove) - Mert Arduino and Tech
#include <EEPROM.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;                   //the library which helps us to control the radio modem

char *msg = "111"; //Total number of data to be sent (data package)

//define the flex sensor input pins

int flex_3 = A5;
int flex_2 = A3;
int flex_1 = A1;

//define variables for flex sensor values

int flex_3_val;
int flex_2_val;
int flex_1_val;

//RF24 radio(9,10);                     //9 and 10 are a digital pin numbers to which signals CE and CSN are connected.                                      
//const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.
//
//
//void setup(void){
//  Serial.begin(9600);
//  radio.begin();                      //it activates the modem.
//  radio.openWritingPipe(pipe);        //sets the address of the receiver to which the program will send data.
//}

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
}

void loop(void){


 
  flex_3_val = analogRead(flex_3);
    flex_2_val = analogRead(flex_2);
    flex_1_val = analogRead(flex_1);
     flex_3_val=map(flex_3_val ,400,600,300,700);
 // Serial.println(flex_3_val);
  //index 
  if(flex_1_val>620 && flex_2_val>550 && flex_3_val>600){
    msg[2]='0';
  }
  else if(flex_1_val<=620 && flex_2_val<=550 && flex_3_val<=600){
    msg="001";
  }
  else if(flex_1_val<=620 && flex_2_val<=550 && flex_3_val>600){
    msg="011";
  }
  else if(flex_1_val>620 && flex_2_val<=550 && flex_3_val<=600){
    msg="101";
  }
  else if(flex_1_val>620 && flex_2_val<=550 && flex_3_val>600){
    msg="111";
  }
    
//msg[0] corresponds to left tyres movement
//msg[1] corresponds to right tyres movement
// msg[2] means motion
// '0'value means backward rotation
// '1' means forward rotation

driver.send((uint8_t *)msg,strlen(msg));
driver.waitPacketSent();
    delay(1);
    Serial.println((char*)msg); 
 // radio.write(msg, sizeof(msg));
}
