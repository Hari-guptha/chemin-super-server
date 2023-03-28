#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 5  // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11  // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "Titan";
const char* password = "12346789";
const int relayPin1 = 16;
const int relayPin2 = 5;
const int relayPin3 = 0;
float h;
float t;
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
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  WiFiClientSecure client;
  // Disable SSL/TLS verification (not recommended for production use)
  client.setInsecure();
  HTTPClient http;
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println(h);
  Serial.println(t);

  // Send a POST request to a URL
  http.begin(client, "https://chemin-server.onrender.com/temphum");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Prepare the request body
  String requestBody = "temp=" + String(t) + "&hum=" + String(h);

  // Send the request and get the response
  int httpCode = http.POST(requestBody);

  // Check the response code
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println(httpCode);
    Serial.println(response);
  } else {
    Serial.println("Error on HTTP request");
  }

  // Disconnect from the server
  http.end();

  delay(2000);
}
