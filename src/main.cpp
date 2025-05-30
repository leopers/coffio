#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include "secrets.h"  // Define ssid and password here

#define RELAY_PIN D1

ESP8266WebServer server(80);
String scheduledTime = "";

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Ensure relay is off at startup

  Serial.begin(115200);
  delay(100);
  Serial.println("📡 Booting Coffio...");

  WiFi.begin(ssid, password);
  Serial.print("🔌 Connecting to WiFi");
  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 30) {
    delay(500);
    Serial.print(".");
    retry++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected!");
    Serial.print("🌐 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to WiFi.");
  }

  // Initialize filesystem
  if (!LittleFS.begin()) {
    Serial.println("❌ Failed to mount LittleFS");
    return;
  }

  // Serve frontend files
  server.serveStatic("/", LittleFS, "/index.html");
  server.serveStatic("/style.css", LittleFS, "/style.css");
  server.serveStatic("/script.js", LittleFS, "/script.js");

  // Relay ON endpoint
  server.on("/on", HTTP_GET, []() {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("🚀 Relay ON (coffee brewing)");
    server.send(200, "text/plain", "Brewing");
  });

  // Relay OFF endpoint
  server.on("/off", HTTP_GET, []() {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("🛑 Relay OFF (brew stopped)");
    server.send(200, "text/plain", "Stopped");
  });

  // Schedule endpoint
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

void loop() {
  server.handleClient();

  // Scheduling logic disabled until real-time support is added
  /*
  String now = getCurrentTime();
  if (scheduledTime.length() && now == scheduledTime) {
    Serial.println("⏰ Scheduled time matched — brewing now!");
    digitalWrite(RELAY_PIN, HIGH);
    delay(10000);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("✅ Brew complete, relay OFF");
    scheduledTime = "";
  }
  */
}

// Placeholder for later use
String getCurrentTime() {
  return "";  // Not implemented yet
}