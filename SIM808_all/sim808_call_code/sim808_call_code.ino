#include <SoftwareSerial.h>
SoftwareSerial sim808(8, 7); // RX, TX pins of SIM808 module

void setup() {
  Serial.begin(9600);
  sim808.begin(9600);
  delay(1000);
}

void loop() {
  // Make a phone call
  sim808.println("ATD+8801849472106;"); // Replace with the phone number you want to call

  // Wait for call to connect
  while (!sim808.find("OK")) {}

  // Wait for call to end
  while (sim808.available()) {
    String response = sim808.readStringUntil('\n');
    if (response.indexOf("NO CARRIER") != -1) {
      // Call has ended
      Serial.println("Call ended");
      break;
    }
  }

  // Wait a few seconds before making another call
  delay(5000);
}
