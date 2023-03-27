#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "AnbuFTTH";
const char* password = "anbu@1964";
const int relayPin1 = 16;
const int relayPin2 = 5;
const int relayPin3 = 0;
String code[3];
unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 0.5;  // 5 seconds

void setup() {
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //delay(1000);
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
    HTTPClient http1;
    // Send a GET request to a URL
    http1.begin(client, "https://chemin-server.onrender.com/fun1");
    // Send the request and get the response
    int httpCode1 = http1.GET();
    String payload1 = http1.getString();
    // Print the response
    Serial.println(httpCode1);
    Serial.println(payload1);
    // Disconnect from the server
    http1.end();

    // Create an HTTP client object
    HTTPClient http2;
    // Send a GET request to a URL
    http2.begin(client, "https://chemin-server.onrender.com/fun2");
    // Send the request and get the response
    int httpCode2 = http2.GET();
    String payload2 = http2.getString();
    // Print the response
    Serial.println(httpCode2);
    Serial.println(payload2);
    // Disconnect from the server
    http2.end();

    // Create an HTTP client object
    HTTPClient http3;
    // Send a GET request to a URL
    http3.begin(client, "https://chemin-server.onrender.com/fun3");
    // Send the request and get the response
    int httpCode3 = http3.GET();
    String payload3 = http3.getString();
    // Print the response
    Serial.println(httpCode3);
    Serial.println(payload3);
    // Disconnect from the server
    http3.end();

    code[0] = payload1;
    code[1] = payload2;
    code[2] = payload3;
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
        continue;
    }
  }
  }