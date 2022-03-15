/*
Light Sleep with External Wake Up
=====================================
This code displays how to use light sleep with
an external trigger as a wake up source and how
to store data in RTC memory to use it over reboots
*/

#include "WiFi.h"

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  200        /* Time ESP32 will go to sleep (in seconds) */

void setup(){
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor

  /*
  First we configure the wake up source
  We set our ESP32 to wake up for an external trigger.
  There are two types for ESP32, ext0 and ext1 .
  ext0 uses RTC_IO to wakeup thus requires RTC peripherals
  to be on while ext1 uses RTC Controller so doesnt need
  peripherals to be powered on.
  Note that using internal pullups/pulldowns also requires
  RTC peripherals to be turned on.
  */
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low


  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_OFF);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop(){
  // Workaround for a bug with scanNetworks() after wakeup from externel source.
  // Scan always fails if WiFi.mode(WIFI_OFF) is not executed before scan.
  WiFi.mode(WIFI_OFF);
  delay(10);
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
      esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

      // Go to sleep now
      Serial.println("going to sleep (200s)");
      delay(10);
      esp_light_sleep_start();
      esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
        // Print BSSID for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.println(WiFi.BSSIDstr(i));
        delay(10);
    }

    // Go to sleep now
    Serial.println("going to sleep");
    delay(10);
    esp_light_sleep_start();
  }
}
