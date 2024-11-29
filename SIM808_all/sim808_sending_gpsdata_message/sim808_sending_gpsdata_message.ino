#include <SoftwareSerial.h>
SoftwareSerial sim808(8, 7); // RX, TX pins of SIM808 module

String data[5];
#define DEBUG true
String state,timegps,latitude,longitude;

void setup() {
  Serial.begin(9600);
  sim808.begin(9600);
  delay(100);

  // Set SMS mode to text mode
  sim808.println("AT+CMGF=1");
  delay(400);

 sendData("AT+CGNSPWR=1",1000,DEBUG);
 delay(50);
 sendData("AT+CGNSSEQ=RMC",1000,DEBUG);
 delay(150);
}


void sendTabData(String command, const int timeout, boolean debug) {
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ((time + timeout) > millis()) {
    while (sim808.available()) {
      char c = sim808.read();
      if (c != ',') {
        data[i] += c;
        delay(100);
      } else {
        i++;
        if (i == 5) {
          delay(100);
          goto exitL;
        }
      }
    }
  }
exitL:
  if (debug) {
    state = data[1];
    timegps = data[2];
    latitude = data[3];
    longitude = data[4];
  }
}


  String sendData (String command , const int timeout ,boolean debug){
  String response = "";
  sim808.println(command);
  long int time = millis();
  int i = 0;

  while ( (time+timeout ) > millis()){
    while (sim808.available()){
      char c = sim808.read();
      response +=c;
    }
  }
  if (debug) {
     Serial.print(response);
     }
     return response;
}




void loop() {
  sendTabData("AT+CGNSINF",1000,DEBUG);
  Serial.println(state);

  if (state != "0") {     //state must be 1
    Serial.println("State  :"+state);
    Serial.println("Time  :"+timegps);
    Serial.println("Latitude  :"+latitude);
    Serial.println("Longitude  :"+longitude);

  
      // Send SMS message with GPS location
      sim808.println("AT+CMGS=\"+8801849472106\""); // Replace with the phone number you want to send the message to
      delay(1000);
      sim808.print("Latitude: ");
      sim808.println(latitude);
      sim808.print("Longitude: ");
      sim808.println(longitude);
    sim808.print("http://maps.google.com/maps?q=loc:");
    sim808.print(latitude);
    sim808.print(",");
    sim808.print (longitude);
      delay(200);
      sim808.println((char)26); // End AT command with a ^Z, ASCII code 26
      delay(200);
      sim808.println();

      // Wait for message to send
      while (!sim808.find("OK")) {}
      sim808.flush();

      // Turn off GPS power to conserve battery
      //sim808.println("AT+CGPSPWR=0");
      //delay(1000);

      // Wait a few seconds before getting another GPS location
      delay(20000);
    }
  }

