#include "hardware/rtc.h"  // For RTC functions
#include "time.h"          // For time handling
#include "Adafruit_NeoPixel.h"  // For NeoPixel control

#include "led_control.h"      // Contains LED control logic
#include "eeprom_storage.h"
#include "WiFiManager.h"
#include "wifi_manager.h"     // Contains Wi-Fi connection and time sync logic
#include "web_server.h"       // Contains the configuration web server logic

const char ENV_TZ[] = "TZ";
const char LOCAL_TZ[] = "CET-1CEST,M3.2.0/2,M10.5.0/3"; // Paris timezone

void setup() {
    Serial.begin(9600);


    setenv(ENV_TZ, LOCAL_TZ, 1);

    pixels.begin();    // Initialize the NeoPixel strip
    pixels.clear();    // Clear all LEDs

    // Initialize the RTC
    rtc_init();

    EEPROM.begin(512);

    // debug remove credential
    // EEPROM.put(0, 10);
    // EEPROM.commit();
    
    if (loadFromEEPROM()) {
      Serial.println("Loading value from eeprom");
    } else {
      Serial.println("Couldn't load from eeprom: default init");
    }

    // Sync time from NTP at startup
    syncTimeOnStartup();  // Wi-Fi connection and time sync

}

void loop() {
    checkConfigTrigger();   // Check if GPIO pin is pulled to ground to start web server

    datetime_t current_time;
    rtc_get_datetime(&current_time);  // Get current time from the RTC

    controlLEDs(current_time);        // LED logic depending on time
    
    delay(1000); // Delay to avoid rapid switching
}
