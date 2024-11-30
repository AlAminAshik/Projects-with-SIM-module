// #include <EspSoftwareSerial>

// Hardware Serial 2 pins
#define RXD2 16
#define TXD2 17

#define text_button 4
#define SOS_button 2
#define SOS_led 23

// // Create a SoftwareSerial object
// SoftwareSerial Serial2(TX_PIN, RX_PIN);

void setup()
{
  //Begin serial communication with nodemcu (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L (D16 RX2 and D17 TX2)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(text_button, INPUT_PULLUP);
  pinMode(SOS_button, INPUT_PULLUP);
  pinMode(SOS_led, OUTPUT);

  Serial2.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void loop()
{
  if(digitalRead(text_button) == LOW){       //if the button is pressed once
    mySerial.println("AT+CMGF=1");  // Configuring TEXT mode
    updateSerial();
    mySerial.println("AT+CMGS=\"+8801849472106\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print("I am in danger, please send help. Location:......."); //text content
    updateSerial();
    mySerial.write(26);   //size of the message
    delay(5000);
  }

  while(digitalRead(SOS_button) == LOW){
    digitalWrite(SOS_led) = HIGH;
    delay(300);
    digitalWrite(SOS_led) = LOW;
    delay(300);
  }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial2.write(Serial.read());//Forward what Serial received to hardware Serial Port
  }
  while(Serial2.available()) 
  {
    Serial.write(Serial2.read());//Forward what hardware Serial received to Serial Port
  }
}