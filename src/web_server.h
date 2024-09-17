#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include "pico/stdlib.h" // Include for Pico-specific functions
#include "pico/time.h"   // Include for RTC functions
#include <LEAmDNS.h>
#include "Global.h"

#define PIN_CONFIG 21

WebServer serverConfig(80); // Web server on port 80
bool serverRunning = false; // Flag to indicate if the server is running

// Function to get the current time from RTC
String getFormattedTime() {
    datetime_t timeinfo;
    rtc_get_datetime(&timeinfo); // Get the time from RTC
    
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", timeinfo.hour, timeinfo.min, timeinfo.sec); // Format as HH:MM:SS
    return String(buffer);
}

const char* configPageTemplate = R"(
<!DOCTYPE html>
<html>
<head>
    <meta name='viewport' content='width=device-width, initial-scale=1, minimum-scale=1'/>
<style>
    body {
        font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        background-color: #22272D;
        color: white;
        text-align: center;
    }

    .title {
        font-size: 28px;
        color: white;
        margin-top: 20px;
    }

    .desc {
        color: #8293A6;
        font-size: 18px;
        margin-top: 10px;
    }

    .label {
        font-size: 16px;
        color: white;
        display: block;
        margin: 10px 0 5px;
    }

    input[type=range], input[type=time] {
        width: 80%;
        padding: 6px;
        margin-bottom: 20px;
        background-color: #33373F;
        color: white;
        border: 1px solid #60BDC5;
        border-radius: 4px;
    }

    .color-container {
        display: flex;
        justify-content: center;
        margin-top: 10px;
    }

    .color-group {
        width: 25.77%;
        margin: 0 1%;
        text-align: left;
    }
    
    input#color_night_light {
        width: 81.5%;  /* Adjust width for this specific color picker */
        height: 50px;
        background-color: #33373F;
        border: 1px solid #60BDC5;
        border-radius: 4px;
        cursor: pointer;
        margin-bottom: 10px;
    }


    input[type=color] {
        width: 100%;
        height: 50px;
        background-color: #33373F;
        border: 1px solid #60BDC5;
        border-radius: 4px;
        cursor: pointer;
    }

    input[type=submit] {
        background-color: #22272D;
        border: 1px solid #60BDC5;
        border-radius: 4px;
        color: #8293A6;
        cursor: pointer;
        padding: 10px 32px;
        font-size: 16px;
        transition-duration: 0.4s;
    }

    input[type=submit]:hover {
        background-color: #60BDC5;
        color: white;
    }

    #confirmationMessage {
        color: green;
        margin-top: 20px;
    }
</style>
</head>
<body>
    <img src="%HEADER_IMAGE%" width="100px" alt="Hero logo"/>
    <div class="title">Configure LED Settings</div>
    <div class="desc">Current Time: <span id="current_time">%TIME%</span></div>
    <form id="configForm">
    <!-- Light Value input -->
    <label class="label" for="light_value">Light Value (0-255):</label>
    <input type="range" id="light_value" name="light_value" min="0" max="255" value="%LIGHT_VALUE%" step="1">

    <label class="label" for="color_night_light">Color Night Light:</label>
    <input type="color" id="color_night_light" name="color_night_light" value="%COLOR_NIGHT_LIGHT%">
    
    <!-- Color inputs in a separate block -->
    <div class="color-container">
        <div class="color-group">
            <label class="label" for="color1">Color 1:</label>
            <input type="color" id="color1" name="color1" value="%COLOR1%">
        </div>

        <div class="color-group">
            <label class="label" for="color2">Color 2:</label>
            <input type="color" id="color2" name="color2" value="%COLOR2%">
        </div>

        <div class="color-group">
            <label class="label" for="color3">Color 3:</label>
            <input type="color" id="color3" name="color3" value="%COLOR3%">
        </div>
    </div>

    <!-- Time inputs for color start times -->
    <label class="label" for="green_start">Color 1 Start Time:</label>
    <input type="time" id="green_start" name="green_start" value="%GREEN_START%">

    <label class="label" for="yellow_start">Color 2 Start Time:</label>
    <input type="time" id="yellow_start" name="yellow_start" value="%YELLOW_START%">

    <label class="label" for="red_start">Color 3 Start Time:</label>
    <input type="time" id="red_start" name="red_start" value="%RED_START%">

    <label class="label" for="off_start">Off Start Time:</label>
    <input type="time" id="off_start" name="off_start" value="%OFF_START%">

    <input type="submit" value="Submit">
</form>

    <div id="confirmationMessage" style="display:none;">Form Submitted Successfully!</div>

    <script>
        document.getElementById('configForm').addEventListener('submit', function(event) {
            event.preventDefault();
            var xhr = new XMLHttpRequest();
            xhr.open('POST', '/update', true);
            xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
            
            var formData = new FormData(document.getElementById('configForm'));
            var params = new URLSearchParams(formData).toString();
            
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    document.getElementById('confirmationMessage').style.display = 'block';
                }
            };
            
            xhr.send(params);
        });
    </script>
</body>
</html>
)";



// Function to replace placeholders in the HTML template
String generateConfigPage() {
    String pageContent = String(configPageTemplate);

    pageContent.replace("%HEADER_IMAGE%", hero_img);
    pageContent.replace("%TIME%", getFormattedTime());

    char buffer[9];

    // LIGHT value
    pageContent.replace("%LIGHT_VALUE%", String(light_value));

    // RGB values for colors (converted to HEX format for color picker)
    char hexcolornightlight[8], hexColor1[8], hexColor2[8], hexColor3[8];

    snprintf(hexcolornightlight, sizeof(hexcolornightlight), "#%02X%02X%02X", (int)(color_night_light[0] * 255), (int)(color_night_light[1] * 255), (int)(color_night_light[2] * 255));
    snprintf(hexColor1, sizeof(hexColor1), "#%02X%02X%02X", (int)(color1_rgb[0] * 255), (int)(color1_rgb[1] * 255), (int)(color1_rgb[2] * 255));
    snprintf(hexColor2, sizeof(hexColor2), "#%02X%02X%02X", (int)(color2_rgb[0] * 255), (int)(color2_rgb[1] * 255), (int)(color2_rgb[2] * 255));
    snprintf(hexColor3, sizeof(hexColor3), "#%02X%02X%02X", (int)(color3_rgb[0] * 255), (int)(color3_rgb[1] * 255), (int)(color3_rgb[2] * 255));

    pageContent.replace("%COLOR_NIGHT_LIGHT%", String(hexcolornightlight));
    pageContent.replace("%COLOR1%", String(hexColor1));
    pageContent.replace("%COLOR2%", String(hexColor2));
    pageContent.replace("%COLOR3%", String(hexColor3));

    // Start times for each color
    snprintf(buffer, sizeof(buffer), "%02d:%02d", color1_start_hour, color1_start_minute);
    pageContent.replace("%GREEN_START%", String(buffer));
    
    snprintf(buffer, sizeof(buffer), "%02d:%02d", color2_start_hour, color2_start_minute);
    pageContent.replace("%YELLOW_START%", String(buffer));

    snprintf(buffer, sizeof(buffer), "%02d:%02d", color3_start_hour, color3_start_minute);
    pageContent.replace("%RED_START%", String(buffer));

    snprintf(buffer, sizeof(buffer), "%02d:%02d", off_start_hour, off_start_minute);
    pageContent.replace("%OFF_START%", String(buffer));

    return pageContent;
}

// Handle the configuration page request
void handleConfigPage() {
    String pageContent = generateConfigPage();
    serverConfig.send(200, "text/html", pageContent);
}

void handleFormSubmission() {
    light_value = serverConfig.arg("light_value").toInt();

    // Extract RGB values from the submitted color hex string
    String colornightligth_hex = serverConfig.arg("color_night_light").substring(1);
    String color1_hex = serverConfig.arg("color1").substring(1);
    String color2_hex = serverConfig.arg("color2").substring(1);
    String color3_hex = serverConfig.arg("color3").substring(1);

    // Convert the hex string to RGB values
    color_night_light[0] = strtol(colornightligth_hex.substring(0, 2).c_str(), NULL, 16) / 255.0;
    color_night_light[1] = strtol(colornightligth_hex.substring(2, 4).c_str(), NULL, 16) / 255.0;
    color_night_light[2] = strtol(colornightligth_hex.substring(4, 6).c_str(), NULL, 16) / 255.0;

    color1_rgb[0] = strtol(color1_hex.substring(0, 2).c_str(), NULL, 16) / 255.0;
    color1_rgb[1] = strtol(color1_hex.substring(2, 4).c_str(), NULL, 16) / 255.0;
    color1_rgb[2] = strtol(color1_hex.substring(4, 6).c_str(), NULL, 16) / 255.0;

    color2_rgb[0] = strtol(color2_hex.substring(0, 2).c_str(), NULL, 16) / 255.0;
    color2_rgb[1] = strtol(color2_hex.substring(2, 4).c_str(), NULL, 16) / 255.0;
    color2_rgb[2] = strtol(color2_hex.substring(4, 6).c_str(), NULL, 16) / 255.0;

    color3_rgb[0] = strtol(color3_hex.substring(0, 2).c_str(), NULL, 16) / 255.0;
    color3_rgb[1] = strtol(color3_hex.substring(2, 4).c_str(), NULL, 16) / 255.0;
    color3_rgb[2] = strtol(color3_hex.substring(4, 6).c_str(), NULL, 16) / 255.0;

    // Parse the start times for each color
    sscanf(serverConfig.arg("green_start").c_str(), "%d:%d:%d", &color1_start_hour, &color1_start_minute, &color1_start_second);
    sscanf(serverConfig.arg("yellow_start").c_str(), "%d:%d:%d", &color2_start_hour, &color2_start_minute, &color2_start_second);
    sscanf(serverConfig.arg("red_start").c_str(), "%d:%d:%d", &color3_start_hour, &color3_start_minute, &color3_start_second);
    sscanf(serverConfig.arg("off_start").c_str(), "%d:%d:%d", &off_start_hour, &off_start_minute, &off_start_second);

    if (saveToEEPROM()) {
        serverConfig.send(200, "text/html", "OK");
    } else {
        serverConfig.send(200, "text/html", "<html><body><h1>Failed to save new config</h1></body></html>");
    }
}

void handleStopRequest() {
    Serial.println("Stopping webserver and wifi");
    // server.send(200, "text/html", "<html><body><h1>Stopping Webserver...</h1></body></html>");
    serverConfig.close();
    WiFi.disconnect();
    serverRunning = false; // Update flag to stop the server loop
}

void startConfigServer() {
    serverConfig.on("/", handleConfigPage);
    serverConfig.on("/update", HTTP_POST, handleFormSubmission);
    serverConfig.on("/stop", HTTP_POST, handleStopRequest);
    serverConfig.begin();
}

void checkConfigTrigger() {
    pinMode(PIN_CONFIG, INPUT_PULLUP);
    if (digitalRead(PIN_CONFIG) == LOW) {
        if (!serverRunning){
        serverRunning = true;
        connectToWiFi();

        if (MDNS.begin("nightlight")) {
          Serial.println("MDNS responder started");
        }
        Serial.println("Starting config server");
        Serial.print("Running on IP Address: ");
        Serial.println(WiFi.localIP());
        
        startConfigServer();
        }else {
            serverConfig.handleClient(); // Handle client requests
            MDNS.update();
            delay(10);
        }

        // while (serverRunning and WiFi.status() == WL_CONNECTED) {
            
        //      // Add a short delay to prevent watchdog timer issues
        // }
    } else {
      if (serverRunning){
        handleStopRequest();
      }
    }
}

#endif // WEB_SERVER_H
