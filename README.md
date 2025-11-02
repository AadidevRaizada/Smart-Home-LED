# Smart Home LED Control System

## Description  
This project controls a LED using a light sensor and a fixed “evening” mode [for demonstration purposes] . The LED turns **ON** when the ambient light is below a threshold *and* it is evening. A web interface displays the LED status and current time.

## Features  
- Evening mode permanently enabled  
- Light sensor input (analog) detects darkness  
- LED output reacts: ON when dark  
- Web interface shows:  
  - Current time (12-hour format with hours, minutes, seconds)  
  - LED status (ON/OFF)  
  - Smooth transitions when status changes  
  - Clear feedback if connection to ESP32 is lost  

## Block Diagram  
<img width="405" height="420" alt="image" src="https://github.com/user-attachments/assets/0eeb76ad-0598-45d5-b8b1-518a43b1187f" />


## Web Interface Panels  
| Panel              | Description                                             |
|---------------------|---------------------------------------------------------|
| LED Status Panel    | Shows whether the LED is ON or OFF                      |
| Time Panel          | Displays current local time in 12-hour format           |
| Connection Feedback | Alerts when connection to ESP32 is interrupted          |
<img width="758" height="407" alt="image" src="https://github.com/user-attachments/assets/11fe4b1a-58ce-4293-94dd-7203548a4780" />
<img width="790" height="466" alt="image" src="https://github.com/user-attachments/assets/ca14d6ee-a14c-4ca3-8050-25937d93541d" />
<img width="736" height="370" alt="image" src="https://github.com/user-attachments/assets/b4814b00-d1ca-4a03-bec2-bc2a8cd4c73d" />


## Hardware Setup  
![WhatsApp Image 2025-11-02 at 23 34 12_ad5191a7](https://github.com/user-attachments/assets/6150393a-d253-4176-8287-b8f18359ad77)
![WhatsApp Image 2025-11-02 at 23 34 28_39c5a2f1](https://github.com/user-attachments/assets/66f0985b-a273-4392-8602-872e22cafe81)

- Sensor connected to pin **32** (analog input)  
- Evening signal forced via pin **27** (digital output)  
- LED connected to pin **22** via appropriate resistor  
- Threshold value for sensor set to **1000** (range 0-4095)  
- ESP32 runs a web server providing JSON status endpoint  

## Getting Started  
1. Flash the ESP32 with the firmware.  
2. Connect ESP32 to WiFi and note its IP address.  
3. Open the web interface in a browser using the ESP32’s IP.  
4. View LED status and time; if the LED appears ON when bright, adjust the sensor threshold.  

## Requirements & Dependencies  
- ESP32 Dev Module  
- Light Sensor (LDR or equivalent)  
- LED + resistor  
- Web browser for the front-end interface  
- Local WiFi network accessible by your device and the browser  

## Notes  
- Evening signal is fixed to ON in this version and cannot be toggled.  
- Adjust the threshold value according to environment lighting for correct behavior.  
- The web interface polls the ESP32 for status and shows connection feedback when polling fails.  
