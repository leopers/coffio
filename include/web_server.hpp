// web_server.hpp
#pragma once

#include <ESP8266WebServer.h>
#include <LittleFS.h>

extern ESP8266WebServer server;

extern String scheduledTime;

void setupWebServer(int relayPin) {
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/script.js", LittleFS, "/script.js");

  server.serveStatic("/cat.jpg", LittleFS, "/cat.jpg");

  server.on("/on", HTTP_GET, [relayPin]() {
    digitalWrite(relayPin, HIGH);
    Serial.println("🚀 Relay ON (coffee brewing)");
    server.send(200, "text/plain", "Brewing");
  });

  server.on("/off", HTTP_GET, [relayPin]() {
    digitalWrite(relayPin, LOW);
    Serial.println("🛑 Relay OFF (brew stopped)");
    server.send(200, "text/plain", "Stopped");
  });

  server.on("/schedule", HTTP_GET, []() {
    if (server.hasArg("time")) {
      scheduledTime = server.arg("time");
      Serial.print("📅 Brew scheduled for: ");
      Serial.println(scheduledTime);
      server.send(200, "text/plain", "Scheduled");
    } else {
      server.send(400, "text/plain", "Missing time");
    }
  });

  server.begin();
  Serial.println("✅ HTTP server started");
}

void handleWebRequests() {
  server.handleClient();
}