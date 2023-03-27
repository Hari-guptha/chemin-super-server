#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Titan";
const char* password = "12346789";
const int relayPin1 = 16;
const int relayPin2 = 4;
const int relayPin3 = 5;
String code[3] ;
unsigned long lastRequestTime = 0;
const unsigned long requestInterval = 0.5; // 5 seconds

void setup() {
  Serial.begin(115200);
  pinMode(relayPin,OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
   // delay(0.5);
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
    String payload[3] = http.getString();

    // Print the response
    Serial.println(httpCode);
    Serial.println(payload);
    code = payload;

    // Disconnect from the server
    http.end();
  }

  // Update the relay based on the code received
  if(code == "1"){
     Serial.println("on");
     digitalWrite(relayPin, HIGH);
  }
  else{
     Serial.println("off");
     digitalWrite(relayPin, LOW);
  }
}
