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

Metro sysTimer = Metro(1);// milliseconds

boolean buttonPressed = false;
boolean connection = false; 
int led = 13;

int buttonTimer = 0;
FlexCAN CANbus(500000);
static CAN_message_t txCANmsg,rxCANmsg;
static CAN_message_t txmsg,rxmsg;

char greeting[5] = "Hey!"; 
char hornId[4] = {'220'};
char honk[6] = "Honk!";
char reply[2] ={'1'};

int txCount,rxCount;
unsigned int txTimer,rxTimer;

uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
int nfet1 = A7;

void setup(void){
  CANbus.begin();
  Serial.begin(115200);
  
  pinMode(led, OUTPUT);
  pinMode(nfet1, INPUT);
  digitalWrite(led, 1);

  delay(2000);
  Serial.println("Hello Teensy 3.1 CAN Test.");
  delay(100);
  Serial.println("This is an introduction to how CAN works");
 
  Serial.println();
  delay(1750);
  Serial.println("To begin let's acknowledge the other members on this network.");
  Serial.println();
  delay(1750);
  Serial.println("To do this we must send a message to see who is on the network.");
  Serial.println();
  delay(1550);
  Serial.println("In this example, we will send out the message 'Hey!' to see who is on the network");
  delay(2000);
  Serial.println("This will allow us to see who is on the network!");
  Serial.println();
  delay(1000);
  Serial.println("Creating message...");
  delay(50);

  txCANmsg.id = 0x221;
  txCANmsg.len = 4;
  txCANmsg.buf[0] = greeting[0];
  txCANmsg.buf[1] = greeting[1];
  txCANmsg.buf[2] = greeting[2];
  txCANmsg.buf[3] = greeting[3];
  Serial.println("Sending your message 'Hey!' onto the network!");
  Serial.print("TxMessage :");
          Serial.print(txCANmsg.buf[0]);
          Serial.print(txCANmsg.buf[1]);
          Serial.print(txCANmsg.buf[2]);
          Serial.println(txCANmsg.buf[3]);
  CANbus.write(txCANmsg);
    
  
  while (!connection){  
  CANbus.read(rxCANmsg);
  if(rxCANmsg.id == 544){
    connection = true;
  }
  }
//   int ID = rxCANmsg.id;
//   //Serial.println(ID,DEC);
//  Serial.println(rxCANmsg.id);
  Serial.println("RxMessage :");
  Serial.print(rxCANmsg.buf[0]);
  Serial.print(rxCANmsg.buf[1]);
  Serial.print(rxCANmsg.buf[2]);
  Serial.print(rxCANmsg.buf[3]);
  Serial.println();
   //if(rxCANmsg.id == 544){
    if (rxCANmsg.buf[0] == hornId[0] && rxCANmsg.buf[1] == hornId[1] && rxCANmsg.buf[2] == hornId[2]){
//      if (connectTest == false){
        //connection = true;
        Serial.println("Let's listen for a response!");
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
        Serial.println();
        Serial.println("\t You are connected to the Horn");
        digitalWrite(led, LOW);
        delay(1500);
        Serial.println("You are now connected to an object!");
        delay(500);
        Serial.println("It looks as if you are connected to the horn!");
        Serial.println();
        delay(500);
        Serial.println("Lets send a second message to the horn!");
        delay(750);
        Serial.println("CAN does not only deal with verification of controllers on a bus");
        Serial.println();
        delay(1000);
        Serial.println("CAN also has the ability to relay information, such as a button being pressed!");
        delay(1000);
        Serial.println("Let's press the button to send a message ('Honk!') to the horn controller!");
        Serial.println();
        delay(1500);
        Serial.println("To proceed, press the blue button to send out a message to the horn controller");
        Serial.println();
        delay(500);
      }
    }

  




// -------------------------------------------------------------
void loop(void){
//  currentMillis = millis();
  if (digitalRead(nfet1)==HIGH){
      delay(30);
        if(digitalRead(nfet1)==HIGH){
//          buttonPressed = true;
          digitalWrite(led, HIGH);
          txmsg.id = 0x221;
          txmsg.len = 5;
          txmsg.buf[0] = honk[0];
          txmsg.buf[1] = honk[1];
          txmsg.buf[2] = honk[2];
          txmsg.buf[3] = honk[3];
          txmsg.buf[4] = honk[4];
         // delay(1);
          CANbus.write(txmsg);
          delay(1);
          CANbus.read(rxCANmsg);
          delay(1);
          digitalWrite(led, LOW);
          //CANbus.read(rxCANmsg);
          if (rxCANmsg.id == 544){
           Serial.print("Rx Message:");
            Serial.println(rxCANmsg.buf[0]);
            if (rxCANmsg.buf[0] == 48 || 49){
          Serial.print("TxMessage :");
          Serial.print(txmsg.buf[0]);
          Serial.print(txmsg.buf[1]);
          Serial.print(txmsg.buf[2]);
          Serial.print(txmsg.buf[3]);
          Serial.println(txmsg.buf[4]);
          delay(100);
           Serial.println("The Horn believes it was honked.");
           delay(100);
        }
        }
    }
  }
}


    


  


