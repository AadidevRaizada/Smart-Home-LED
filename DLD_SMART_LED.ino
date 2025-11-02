#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid     = "Raheja3";
const char* password = "88888888";

const int sensorPin  = 32;    // analog input for LDR
const int eveningPin = 27;    // digital output for eveningSignal
const int ledPin     = 22;    // LED output

const int threshold  = 1000;  // 0-4095 range for dark/light

bool eveningSignal = true;    // always evening
bool darkSignal    = false;
bool finalOutput   = false;
bool systemEnabled = true;    // new variable: system ON/OFF

WebServer server(80);

void handleStatus() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  String json = "{";
    json += "\"systemEnabled\":" + String(systemEnabled ? 1 : 0) + ",";
    json += "\"eveningSignal\":" + String(eveningSignal ? 1 : 0) + ",";
    json += "\"darkSignal\":"    + String(darkSignal    ? 1 : 0) + ",";
    json += "\"finalOutput\":"   + String(finalOutput   ? 1 : 0);
  json += "}";
  server.send(200, "application/json", json);
}

void handleToggle() {
  if (server.hasArg("enabled")) {
    systemEnabled = (server.arg("enabled") == "1");
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", systemEnabled ? "1" : "0");
}

void setup(){
  Serial.begin(115200);
  delay(1000);
  pinMode(eveningPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(eveningPin, HIGH);
  Serial.println("Evening signal forced ON");

  Serial.print("Connecting to WiFi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/status", HTTP_GET, handleStatus);
  server.on("/toggle", HTTP_GET, handleToggle);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();

  if (systemEnabled) {
    int sensorValue = analogRead(sensorPin);
    Serial.print("Sensor = ");
    Serial.println(sensorValue);
    darkSignal = (sensorValue < threshold);

    if (darkSignal) {
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }

    finalOutput = (eveningSignal && darkSignal);
  } else {
    // System disabled: keep outputs off (or safe state)
    darkSignal  = false;
    finalOutput = false;
    digitalWrite(ledPin, HIGH); // LED OFF when system disabled
  }

  Serial.print("systemEnabled = ");
  Serial.print(systemEnabled);
  Serial.print(" | eveningSignal = ");
  Serial.print(eveningSignal);
  Serial.print(" | darkSignal = ");
  Serial.print(darkSignal);
  Serial.print(" | finalOutput = ");
  Serial.println(finalOutput);

  delay(1000);
}
