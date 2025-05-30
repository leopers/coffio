// scheduler.hpp
#pragma once

#include <Arduino.h>
#include <time.h>

extern String scheduledTime;

void setupScheduler(int relayPin) {
  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("⏳ Syncing time");
  while (time(nullptr) < 100000) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n🕒 Time synced!");
}

String getCurrentTime() {
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);

  char buf[6];
  snprintf(buf, sizeof(buf), "%02d:%02d", t->tm_hour, t->tm_min);
  return String(buf);
}

void checkAndTriggerSchedule(int relayPin) {
  static String lastCheckedTime = "";
  String now = getCurrentTime();

  if (now != lastCheckedTime) {
    lastCheckedTime = now;
    Serial.print("🕒 Current time: ");
    Serial.println(now);

    if (scheduledTime.length() && now == scheduledTime) {
      Serial.println("⏰ Scheduled time matched — brewing now!");
      digitalWrite(relayPin, HIGH);
      delay(10000); // Brew duration
      digitalWrite(relayPin, LOW);
      Serial.println("✅ Brew complete, relay OFF");
      scheduledTime = "";
    }
  }
}