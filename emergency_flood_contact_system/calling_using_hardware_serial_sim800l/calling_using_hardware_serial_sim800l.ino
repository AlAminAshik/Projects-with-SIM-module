// #include <EspSoftwareSerial>

// Hardware Serial 2 pins
#define RXD2 16
#define TXD2 17

// // Create a SoftwareSerial object
// SoftwareSerial Serial2(TX_PIN, RX_PIN);

void setup()
{
  //Begin serial communication with nodemcu (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L (D16 RX2 and D17 TX2)
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(14, INPUT_PULLUP); //

  Serial2.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void loop()
{
  if(digitalRead(14) == LOW){       //if the button is pressed once
    Serial.println("button pressed");
    Serial2.println("ATD+ +8801849472106;");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    delay(15000);
    Serial2.println("ATH");
    updateSerial();
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