// web_server.hpp
#pragma once

#include <ESP8266WebServer.h>
#include <LittleFS.h>

extern ESP8266WebServer server;

extern String scheduledTime;

extern bool isBrewing;
extern unsigned long brewStartTime;

void setupWebServer(int relayPin) {
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/script.js", LittleFS, "/script.js");

  server.serveStatic("/cat.jpg", LittleFS, "/cat.jpg");

  server.on("/on", HTTP_GET, [relayPin]() {
    if (!isBrewing) {
      digitalWrite(relayPin, HIGH);
      isBrewing     = true;
      brewStartTime = millis();
      Serial.println("Relay ON (coffee brewing, not-blocking)");
      server.send(200, "text/plain", "Brewing (will auto‐stop in 30 s)");
    } else {
      server.send(400, "text/plain", "Already brewing");
    }
  });

  server.on("/off", HTTP_GET, [relayPin]() {
    if (isBrewing) {
      digitalWrite(relayPin, LOW);
      isBrewing = false;
      Serial.println("Relay OFF (brew stopped)");
      server.send(200, "text/plain", "Stopped");
    } else {
      server.send(400, "text/plain", "Não havia brewing");
    }
  });

  server.on("/schedule", HTTP_GET, []() {
    if (server.hasArg("time")) {
      scheduledTime = server.arg("time");
      Serial.print("Brew scheduled for: ");
      Serial.println(scheduledTime);
      server.send(200, "text/plain", "Scheduled");
    } else {
      server.send(400, "text/plain", "Missing time");
    }
  });

  server.on("/cancel", HTTP_GET, [relayPin]() {
    if (isBrewing) {
      digitalWrite(relayPin, LOW);
      isBrewing = false;
      Serial.println("Brew canceled.");
      server.send(200, "text/plain", "Canceled");
    } else {
      scheduledTime = "";
      Serial.println("Cancelado agendamento (se havia).");
      server.send(200, "text/plain", "Canceled");
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void handleWebRequests() {
  server.handleClient();
}