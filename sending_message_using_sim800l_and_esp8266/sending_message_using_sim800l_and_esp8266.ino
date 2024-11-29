#include <SoftwareSerial.h>

// Define RX and TX pins for SoftwareSerial
#define wemos_TX_PIN 0 //D3
#define wemos_RX_PIN 2 //D4

// Create a SoftwareSerial object
SoftwareSerial mySerial(wemos_TX_PIN, wemos_RX_PIN);

void setup()
{
  //Begin serial communication with nodemcu (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  pinMode(14, INPUT_PULLUP); //D5

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void loop()
{
  if(digitalRead(14) == LOW){       //if the button is pressed once
    mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+8801849472106\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print("Last Minute Engineers | lastminuteengineers.com"); //text content
    updateSerial();
    mySerial.write(26);   //size of the message
    delay(5000);
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}