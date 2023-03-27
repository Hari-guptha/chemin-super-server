#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Titan";
const char* password = "12346789";
const int relayPin1 = 16;
const int relayPin2 = 4;
const int relayPin3 = 5;
String code[3];
unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 5000;  // 5 seconds

void setup() {
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check if it's time to make a request
  if (millis() - lastRequestTime > requestInterval) {
    lastRequestTime = millis();

    // Create a WiFi client object with SSL/TLS support
    WiFiClientSecure client;

    // Disable SSL/TLS verification (not recommended for production use)
    client.setInsecure();

    // Create an HTTP client object
    HTTPClient http;

    // Send a GET request to a URL
    http.begin(client, "https://esp-qs0v.onrender.com/fun");

    // Send the request and get the response
    int httpCode = http.GET();
    String payload = http.getString();

    // Print the response
    Serial.println(httpCode);
    Serial.println(payload);
    code[0] = payload.substring(0,1);
    code[1] = payload.substring(1,2);
    code[2] = payload.substring(2,3);

    // Disconnect from the server
    http.end();
  }

  // Loop through each string in the array
  for (int i = 0; i < 3; i++) {

    // Get the current string from the array
    String currentString = code[i];

    // Use a switch case to check the value of the current string
    switch (currentString.toInt()) {

      case 1:
        Serial.println();
        digitalWrite(relayPin1, HIGH);
        continue;

      case 2:
        Serial.println("l1 off");
        digitalWrite(relayPin1, LOW);
        continue;
      case 3:
        Serial.println("l2 on");
        digitalWrite(relayPin2, HIGH);
        continue;

      case 4:
        Serial.println("l2 off");
        digitalWrite(relayPin2, LOW);
       continue;
      case 5:
        Serial.println("l3 on");
        digitalWrite(relayPin3, HIGH);
        continue;

      case 6:
        Serial.println("l3 off");
        digitalWrite(relayPin3, LOW);
    }
  }
}
