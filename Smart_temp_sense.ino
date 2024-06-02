#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D2          // What digital pin we're connected to
#define DHTTYPE DHT11      // DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// Replace with your network credentials
const char* ssid = "ROCKSTAR";
const char* password = "1234567890";

ESP8266WebServer server(80); // Server on port 80

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);             // Connect to the network
  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);      // Call the 'handleRoot' function when a client requests URI "/"
  server.begin();                  // Actually start the server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle client requests
}

void handleRoot() { // Function to be called when a client requests "/"
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature as Celsius (the default)

  String message = "<html><head><title>ESP8266 DHT Server</title></head><body><h1>Temperature and Humidity</h1>";
  message += "<p>Temperature: ";
  message += t;
  message += "°C</p>";
  message += "<p>Humidity: ";
  message += h;
  message += "%</p>";
  message += "</body></html>";

  server.send(200, "text/html", message); // Send HTTP status 200 (Ok) and send some text to the browser/client
}
