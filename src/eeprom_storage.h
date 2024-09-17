#include <EEPROM.h>

#define MAGIC_NUMBER 117  // A predefined number to indicate valid EEPROM data

// Function to save data to EEPROM with a magic number
bool saveToEEPROM() {
   int address = 128;

  // Save the magic number first
  EEPROM.write(address++, MAGIC_NUMBER);

  // Save light value
  EEPROM.write(address++, light_value);

  // Save green start time
  EEPROM.write(address++, color1_start_hour);
  EEPROM.write(address++, color1_start_minute);
  EEPROM.write(address++, color1_start_second);

  // Save yellow start time
  EEPROM.write(address++, color2_start_hour);
  EEPROM.write(address++, color2_start_minute);
  EEPROM.write(address++, color2_start_second);

  // Save red start time
  EEPROM.write(address++, color3_start_hour);
  EEPROM.write(address++, color3_start_minute);
  EEPROM.write(address++, color3_start_second);

  // Save off start time
  EEPROM.write(address++, off_start_hour);
  EEPROM.write(address++, off_start_minute);
  EEPROM.write(address++, off_start_second);

  // Save RGB values for color_night_light
  EEPROM.write(address++, color_night_light[0] * 255);  // Red component
  EEPROM.write(address++, color_night_light[1] * 255);  // Green component
  EEPROM.write(address++, color_night_light[2] * 255);  // Blue component

  // Save RGB values for color_1
  EEPROM.write(address++, color1_rgb[0] * 255);  // Red component
  EEPROM.write(address++, color1_rgb[1] * 255);  // Green component
  EEPROM.write(address++, color1_rgb[2] * 255);  // Blue component

  // Save RGB values for color_2
  EEPROM.write(address++, color2_rgb[0] * 255);  // Red component
  EEPROM.write(address++, color2_rgb[1] * 255);  // Green component
  EEPROM.write(address++, color2_rgb[2] * 255);  // Blue component

  // Save RGB values for color_3
  EEPROM.write(address++, color3_rgb[0] * 255);  // Red component
  EEPROM.write(address++, color3_rgb[1] * 255);  // Green component
  EEPROM.write(address++, color3_rgb[2] * 255);  // Blue component

  Serial.print("Writing until address: ");
  Serial.println(address);

  if (EEPROM.commit()) {
      Serial.println("EEPROM successfully committed");
      return true;
  } else {
      Serial.println("ERROR! EEPROM commit failed");
      return false;
  }
}

// Function to load data from EEPROM with a magic number check
bool loadFromEEPROM() {
  int address = 128;

  // Check the magic number
  if (EEPROM.read(address++) != MAGIC_NUMBER) {
    Serial.println("EEPROM data not found or corrupted. Aborting...");
    return false;
  }

  // Load light value
  light_value = EEPROM.read(address++);

  // Load green start time
  color1_start_hour = EEPROM.read(address++);
  color1_start_minute = EEPROM.read(address++);
  color1_start_second = EEPROM.read(address++);

  // Load yellow start time
  color2_start_hour = EEPROM.read(address++);
  color2_start_minute = EEPROM.read(address++);
  color2_start_second = EEPROM.read(address++);

  // Load red start time
  color3_start_hour = EEPROM.read(address++);
  color3_start_minute = EEPROM.read(address++);
  color3_start_second = EEPROM.read(address++);

  // Load off start time
  off_start_hour = EEPROM.read(address++);
  off_start_minute = EEPROM.read(address++);
  off_start_second = EEPROM.read(address++);

    // Load RGB values for color_1
  color_night_light[0] = EEPROM.read(address++) / 255.0;  // Red component
  color_night_light[1] = EEPROM.read(address++) / 255.0;  // Green component
  color_night_light[2] = EEPROM.read(address++) / 255.0;  // Blue component

  // Load RGB values for color_1
  color1_rgb[0] = EEPROM.read(address++) / 255.0;  // Red component
  color1_rgb[1] = EEPROM.read(address++) / 255.0;  // Green component
  color1_rgb[2] = EEPROM.read(address++) / 255.0;  // Blue component

  // Load RGB values for color_2
  color2_rgb[0] = EEPROM.read(address++) / 255.0;  // Red component
  color2_rgb[1] = EEPROM.read(address++) / 255.0;  // Green component
  color2_rgb[2] = EEPROM.read(address++) / 255.0;  // Blue component

  // Load RGB values for color_3
  color3_rgb[0] = EEPROM.read(address++) / 255.0;  // Red component
  color3_rgb[1] = EEPROM.read(address++) / 255.0;  // Green component
  color3_rgb[2] = EEPROM.read(address++) / 255.0;  // Blue component

  Serial.print("Reading until address: ");
  Serial.println(address);

  return true;  // Successfully loaded data
}
