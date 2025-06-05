// main.cpp
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include "secrets.h"
#include "web_server.hpp"
#include "scheduler.hpp"

#define RELAY_PIN D1

bool isBrewing = false;
unsigned long brewStartTime = 0;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(115200);
  delay(100);
  Serial.println("Booting Coffio...");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 30) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi.");
  }

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS");
    return;
  }

  setupWebServer(RELAY_PIN);
  setupScheduler(RELAY_PIN);
}

void loop() {
  handleWebRequests();
  checkAndTriggerSchedule(RELAY_PIN);

  if (isBrewing && (millis() - brewStartTime >= 30000UL)) {
    digitalWrite(RELAY_PIN, LOW);
    isBrewing = false;
    Serial.println("☕ Brew complete (30 s elapsed).");
  }
}