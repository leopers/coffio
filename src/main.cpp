#include <Arduino.h>

#define RELAY_PIN D1  // GPIO5

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start with relay OFF
  Serial.begin(115200);         // Start serial communication
  Serial.println("Setup complete");
}

void loop() {
  Serial.println("Relay ON");
  digitalWrite(RELAY_PIN, HIGH);  // Simulate turning ON relay
  delay(5000);

  Serial.println("Relay OFF");
  digitalWrite(RELAY_PIN, LOW);   // Simulate turning OFF relay
  delay(5000);
}