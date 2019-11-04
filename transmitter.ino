//Transmitter Code (Glove) - Mert Arduino and Tech
#include <EEPROM.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;                   //the library which helps us to control the radio modem

char *msg = "000"; //Total number of data to be sent (data package)

//define the flex sensor input pins

int flex_3 = A3;
int flex_2 = A2;
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
  Serial.println(flex_3_val);
  //pinky
  if(flex_3_val>550)
    msg[2]='1';
  else{
    msg[2] ='0';

//thumb
    flex_1_val = analogRead(flex_1);
  if(flex_1_val>550)
   { msg[0]='1';
    msg[1]='1';}
  
  else{

    
   flex_2_val = analogRead(flex_2);
   //for left
  if(flex_2_val>550)
    {msg[0] = '0';
    msg[1]='1';}
    //for right
  else
    {msg[0] = '1';
    msg[1]='0';}

 }
 }

    
//msg[0] corresponds to left tyres movement
//msg[1] corresponds to right tyres movement
// msg[2] means stop 
// '0'value means backward rotation
// '1' means forward rotation

driver.send((uint8_t *)msg,strlen(msg));
driver.waitPacketSent();
    delay(1);
 // radio.write(msg, sizeof(msg));
}
