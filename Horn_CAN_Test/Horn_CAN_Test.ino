// -------------------------------------------------------------
// CANtest for Teensy 3.1
// by teachop
//
// This test is talking to a single other echo-node on the bus.
// 6 frames are transmitted and rx frames are counted.
// Tx and rx are done in a way to force some driver buffering.
// Serial is used to print the ongoing status.
//

#include <Metro.h>
#include <FlexCAN.h>

Metro sysTimer = Metro(1);

int nfet2 = 21;
int led = 13;
FlexCAN CANbus(500000);
static CAN_message_t txCANmsg,rxCANmsg;

char greeting[5] = "Hey!";                                                           
char identifier[4] = {'220'};
char honk[6] = "Honk!";
char reply[2] = {'1'};
uint8_t tempMessage[8];

int txCount,rxCount;
unsigned int txTimer,rxTimer;

uint32_t currentMillis = 0;
uint32_t previousMillis = 0;


void setup(void)
{
  CANbus.begin();
  Serial.begin(115200);
  
  pinMode(led, OUTPUT);
  pinMode(nfet2, OUTPUT);
  digitalWrite(led, 1);

  delay(1000);
  Serial.println("Hello! I am the horn controller!");
  Serial.println();
  delay(750);
  Serial.println("Obviously I have power, I'm glad you got that taken care of.");
  Serial.println();
  delay(1500);
  Serial.println("Well here goes nothing.");
  delay(2000);
  Serial.println();
  Serial.println("...");
  Serial.println();
  delay(3000);
  Serial.println("I guess I'm ready to take orders from here boss!");
  delay(700);
  Serial.println();


  

   
}


// -------------------------------------------------------------
void loop(void){
  
  currentMillis = millis();
 
 while(CANbus.read(rxCANmsg)){
  int ID = rxCANmsg.id;
  Serial.print("Wow! Someone talked to me! His Identifier is ID-");
  Serial.println(ID,HEX); 
  Serial.print("This is the message I received: ");
 for (int i = 0; i < rxCANmsg.len; i++)
  {
    Serial.print(rxCANmsg.buf[i]);
  }
  Serial.println();
   if (rxCANmsg.id == 0x221){
    if(rxCANmsg.buf[0] == greeting[0] && rxCANmsg.buf[1] == greeting[1] && rxCANmsg.buf[2] == greeting[2] && rxCANmsg.buf[3] == greeting[3]){
     digitalWrite(led, HIGH);
     txCANmsg.id = 0x220;
     txCANmsg.len = 3;
     Serial.println();
     Serial.println("Let me introduce myself to this guy!");
     Serial.println();
     delay(750);
     Serial.println("I am ID-220. Sending identification...");
     Serial.println();
     delay(1000);
     txCANmsg.buf[0] = identifier[0];
     txCANmsg.buf[1] = identifier[1];
     txCANmsg.buf[2] = identifier[2]; 
     CANbus.write(txCANmsg);
     delay(100);
     digitalWrite(led, LOW);
     Serial.println("Well I guess we will see what he says, I told him who I was.");
   }
   else if(rxCANmsg.buf[0] == honk[0] && rxCANmsg.buf[1] == honk[1] && rxCANmsg.buf[2] == honk[2] && rxCANmsg.buf[3] == honk[3] && rxCANmsg.buf[4] == honk[4]){
     //Serial.println("He talked to me again!");
     delay(1000);
     Serial.println("There seems to be a rumbly in my tumbly...");
     delay(2250);
     digitalWrite(led, HIGH);
     digitalWrite(nfet2, HIGH);
     delay(75);
     digitalWrite(nfet2,LOW);
     txCANmsg.id = 0x220;
     txCANmsg.len = 1;
     txCANmsg.buf[0] = reply[0];
     Serial.println("Excuse me. It must have been the burrito I had last night... :/");
     delay(1000);
     CANbus.write(txCANmsg);
     delay(100);
     digitalWrite(led, LOW);
   }
   }
 }
}
    
