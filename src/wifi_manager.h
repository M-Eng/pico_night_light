#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <time.h>


// Function to scan and display available WiFi networks
void scanNetworks() {
    Serial.println("Scanning for networks...");
    int n = WiFi.scanNetworks();
    if (n == 0) {
        Serial.println("No networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found:");
        for (int i = 0; i < n; ++i) {
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(" dBm) ");
            Serial.println((WiFi.encryptionType(i) == CYW43_AUTH_OPEN) ? "Open" : "Encrypted");
            delay(10);  // Small delay for stability
        }
    }
}

void connectToWiFi() {

    bool debug = false;

    String title("Wifi Setup");
    String name("nightlight.local");
    String maker("M. Engilberge");
    String version("1.0");
   

    WiFiManager wm("PicoLightSetup", "pico_ap_password", debug);   // Access point 
    wm.setContentText(title, name, maker, version);
    bool success = wm.autoConnect();
    
    // Connection established
    Serial.println("");
    Serial.print("Pico W is connected to WiFi network ");
    Serial.println(WiFi.SSID());
  
    // Print IP Address
    Serial.print("Assigned IP Address: ");
    Serial.println(WiFi.localIP());
}

// Function to sync time using NTP
void syncTimeOnStartup() {

    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, light_value, 0, 0)); // Green
    pixels.setPixelColor(1, pixels.Color(0, light_value, 0, 0)); // Green
    pixels.setPixelColor(2, pixels.Color(0, light_value, 0, 0)); // Green
    pixels.show();

    delay(2000);
    scanNetworks();

    delay(400);

    connectToWiFi();

    configTime(10, 0, "pool.ntp.org", "fr.pool.ntp.org");
    Serial.println("Waiting for time sync...");

    time_t now = time(nullptr);
    struct tm timeinfo;
    while (now < 1000000000) {  // Wait for a valid time
        delay(1000);
        now = time(nullptr);
    }
    localtime_r(&now, &timeinfo);

    Serial.println("Time synchronized from NTP server");
    Serial.print("Current time: ");
    Serial.print(timeinfo.tm_year + 1900);
    Serial.print("-");
    Serial.print(timeinfo.tm_mon + 1);
    Serial.print("-");
    Serial.print(timeinfo.tm_mday);
    Serial.print(" ");
    Serial.print(timeinfo.tm_hour);
    Serial.print(":");
    Serial.print(timeinfo.tm_min);
    Serial.print(":");
    Serial.println(timeinfo.tm_sec);

    datetime_t current_time = { 
      .year = timeinfo.tm_year + 1900,
      .month = timeinfo.tm_mon + 1,
      .day = timeinfo.tm_mday,
      .hour = timeinfo.tm_hour,
      .min = timeinfo.tm_min,
      .sec = timeinfo.tm_sec
    };
    
    // Set RTC time
    rtc_set_datetime(&current_time);

    WiFi.disconnect(); // Disconnect Wi-Fi after time sync

    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(light_value, 0, 0, 0)); // Green
    pixels.setPixelColor(1, pixels.Color(light_value, 0, 0, 0)); // Green
    pixels.setPixelColor(2, pixels.Color(light_value, 0, 0, 0)); // Green
    pixels.show();

    delay(3000);
}

#endif // WIFI_MANAGER_H
