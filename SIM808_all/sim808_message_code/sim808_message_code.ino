#include <SoftwareSerial.h>
SoftwareSerial sim808(8, 7); // RX, TX pins of SIM808 module

void setup() {
  Serial.begin(9600);
  sim808.begin(9600);
  delay(1000);

  // Set SMS mode to text mode
  sim808.println("AT+CMGF=1");
  delay(1000);
}

void loop() {
  // Send an SMS message
  sim808.println("AT+CMGS=\"+8801849472106\""); // Replace with the phone number you want to send the message to
  delay(1000);
  sim808.print("Hello, this is a test message from my Arduino!"); // Replace with the message you want to send
  sim808.write(26); // End the message with a Ctrl-Z character

  // Wait for message to send
  while (!sim808.find("OK")) {}

  // Wait a few seconds before sending another message
  delay(5000);
}
