#include <ESP8266WiFi.h>

const char* ssid = "yourssid";
const char* password = "yourpass";

int Pin2 = D2;
int Pin5 = D5;
int Pin6 = D6;
int Pin7 = D7;
int value2 = LOW;
int value5 = LOW;
int value6 = LOW;
int value7 = LOW;
int web = 0;
WiFiServer server(80);

void setup() {

  Serial.begin(115200);
  delay(10);

  pinMode(Pin2, OUTPUT);
  digitalWrite(Pin2, LOW);
  pinMode(Pin5, OUTPUT);
  digitalWrite(Pin5, LOW);
  pinMode(Pin6, INPUT);
  pinMode(Pin7, INPUT);
  // Connect to WiFi network
  Serial.println("\n\n");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void physicalButtons() {

  value6 = digitalRead(Pin6);
  value7 = digitalRead(Pin7);
  if (value6 == 1 && value7 == 0) {
    digitalWrite(Pin2, HIGH);
    value2 = HIGH;
    digitalWrite(Pin5, LOW);
    value5 = LOW;
    web = 0;
  }
  if (value6 == 0 && value7 == 1) {
    digitalWrite(Pin2, LOW);
    value2 = LOW;
    digitalWrite(Pin5, HIGH);
    value5 = HIGH;
    web = 0;
  }
  if (value6 == value7 && web == 0) {
    digitalWrite(Pin2, LOW);
    value2 = LOW;
    digitalWrite(Pin5, LOW);
    value5 = LOW;
  }

}

void serverLoop() {

  // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  if (request.indexOf("/LED0=ON"  && value6 == 0 && value7 == 0) != -1) {
    digitalWrite(Pin2, HIGH);
    value2 = HIGH;
    web = 1;
  }
  if (request.indexOf("/LED0=OFF") != -1) {
    digitalWrite(Pin2, LOW);
    value2 = LOW;
    web = 0;
  }
  if (request.indexOf("/LED1=ON"  && value6 == 0 && value7 == 0) != -1) {
    digitalWrite(Pin5, HIGH);
    value5 = HIGH;
    web = 1;
  }
  if (request.indexOf("/LED1=OFF") != -1) {
    digitalWrite(Pin5, LOW);
    value5 = LOW;
    web = 0;
  }
  if (request.indexOf("/LED0=OFF&LED1=ON") != -1) {
    digitalWrite(Pin2, LOW);
    value2 = LOW;
    digitalWrite(Pin5, HIGH);
    value5 = HIGH;
    web = 1;
  }
  if (request.indexOf("/LED0=ON&LED1=OFF") != -1) {
    digitalWrite(Pin2, HIGH);
    value2 = HIGH;
    digitalWrite(Pin5, LOW);
    value5 = LOW;
    web = 1;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");


  client.print("<br>Pines interruptores: ");

  client.print("<br>Led pin2: ");

  if (value2 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.print("<br>Led pin 5: ");

  if (value5 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED0=OFF&LED1=ON\">SAFE 1 ON</a><br>");
  client.println("<a href=\"/LED1=ON\">1 ON</a><br>");
  client.println("<a href=\"/LED1=OFF\">1 OFF</a><br>");
  client.println("</html>");
  client.println("<br><br>");
  client.println("<a href=\"/LED0=ON&LED1=OFF\">SAFE 0 ON</a><br>");
  client.println("<a href=\"/LED0=ON\">0 ON</a><br>");
  client.println("<a href=\"/LED0=OFF\">0 OFF</a><br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

void loop() {
    serverLoop();
    physicalButtons();
}
