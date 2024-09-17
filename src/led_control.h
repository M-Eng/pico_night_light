#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "Global.h"
#include "printf.h"

#define PIN_PIXEL 28  // Pin connected to the NeoPixels
#define PIN_LIGHT_MODE 10
#define NUMPIXELS 3   // Number of NeoPixels (3 for traffic light)

// Global Variables
int light_value = 128;
int color1_start_hour = 20, color1_start_minute = 0, color1_start_second = 0;
int color2_start_hour = 7, color2_start_minute = 0, color2_start_second = 0;
int color3_start_hour = 7, color3_start_minute = 30, color3_start_second = 0;
int off_start_hour = 8, off_start_minute = 45, off_start_second = 0;

// Define RGB values for color 1, 2, and 3 (0-1 range)
float color_night_light[3] = {0.0, 0.0, 0.0};  // Green (color 1)
float color1_rgb[3] = {0.0, 1.0, 0.0};  // Green (color 1)
float color2_rgb[3] = {1.0, 1.0, 0.0};  // Yellow (color 2)
float color3_rgb[3] = {1.0, 0.0, 0.0};  // Red (color 3)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_PIXEL, NEO_RGBW);

// Function to check if current time is within two specified times (24-hour format)
bool isTimeWithin(int currentHour, int currentMinute, int currentSecond, 
                  int startHour, int startMinute, int startSecond, 
                  int endHour, int endMinute, int endSecond) {

    // Convert all times to seconds since the start of the day
    int currentTimeInSeconds = currentHour * 3600 + currentMinute * 60 + currentSecond;
    int startTimeInSeconds = startHour * 3600 + startMinute * 60 + startSecond;
    int endTimeInSeconds = endHour * 3600 + endMinute * 60 + endSecond;

    // Check if the time range crosses midnight
    if (startTimeInSeconds <= endTimeInSeconds) {
        // Normal time range (start <= end)
        return currentTimeInSeconds >= startTimeInSeconds && currentTimeInSeconds <= endTimeInSeconds;
    } else {
        // Time range spans across midnight (start > end)
        return currentTimeInSeconds >= startTimeInSeconds || currentTimeInSeconds <= endTimeInSeconds;
    }
}

void setPixelColor(int pixel, float rgb[3]) {
    uint8_t r = rgb[0] * light_value;  // Red component
    uint8_t g = rgb[1] * light_value;  // Green component
    uint8_t b = rgb[2] * light_value;  // Blue component
    pixels.setPixelColor(pixel, pixels.Color(g, r, b, 0));  // Set the color with the RGB values
}

void controlLEDs(datetime_t current_time) {
    int currentHour = current_time.hour;
    int currentMinute = current_time.min;
    int currentSecond = current_time.sec;

    pinMode(PIN_LIGHT_MODE, INPUT_PULLUP);

    if (digitalRead(PIN_LIGHT_MODE) == LOW) {
      pixels.clear();
      if (color_night_light[0] == 1.0 && color_night_light[1] == 1.0 && color_night_light[2] == 1.0) {
        for (int i = 0; i < NUMPIXELS; i++) {
            pixels.setPixelColor(i, pixels.Color(light_value, light_value, light_value, light_value));
        }
      } else {
          for (int i = 0; i < NUMPIXELS; i++) {
            setPixelColor(i, color_night_light);  // Color 1 (Green)
          }
      }
      pixels.show();
    } else {
        if (isTimeWithin(currentHour, currentMinute, currentSecond, color1_start_hour, color1_start_minute, color1_start_second, color2_start_hour, color2_start_minute, color2_start_second)) {
            pixels.clear();
            setPixelColor(0, color1_rgb);  // Color 1 (Green)
        } else if (isTimeWithin(currentHour, currentMinute, currentSecond, color2_start_hour, color2_start_minute, color2_start_second, color3_start_hour, color3_start_minute, color3_start_second)) {
            pixels.clear();
            setPixelColor(1, color2_rgb);  // Color 2 (Yellow)
        } else if (isTimeWithin(currentHour, currentMinute, currentSecond, color3_start_hour, color3_start_minute, color3_start_second, off_start_hour, off_start_minute, off_start_second)) {
            pixels.clear();
            setPixelColor(2, color3_rgb);  // Color 3 (Red)
        } else {
            pixels.clear();
        }

        pixels.show();
    }
}

#endif // LED_CONTROL_H