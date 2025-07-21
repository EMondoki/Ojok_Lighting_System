#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Erick Free"; 
const char* password = "vfiv4949"; 

// LED pins
const int led1 = 27;
const int led2 = 26;
const int led3 = 25;

WebServer server(80);

// HTML for the dashboard
String getHTML() {
  String html = R"=====(
  <!DOCTYPE html>
  <html>
  <head>
    <title>[YourName] Systems - Lighting Control</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 20px;
        background-color: #f0f0f0;
        text-align: center;
      }
      .container {
        max-width: 600px;
        margin: 0 auto;
        background: white;
        padding: 20px;
        border-radius: 10px;
        box-shadow: 0 0 10px rgba(0,0,0,0.1);
      }
      h1 {
        color: #2c3e50;
        font-size: 24px;
      }
      .button {
        display: inline-block;
        padding: 10px 20px;
        margin: 10px;
        border: none;
        border-radius: 5px;
        cursor: pointer;
        font-size: 16px;
        transition: background-color 0.3s;
      }
      .button-on { background-color: #27ae60; color: white; }
      .button-off { background-color: #c0392b; color: white; }
      .button:hover { opacity: 0.8; }
      .footer {
        margin-top: 20px;
        font-size: 14px;
        color: #666;
      }
    </style>
  </head>
  <body>
    <div class="container">
      <h1>[YourName] Systems Lighting Control</h1>
      <div>
        <h2>LED 1</h2>
        <a href="/led1/on"><button class="button button-on">ON</button></a>
        <a href="/led1/off"><button class="button button-off">OFF</button></a>
      </div>
      <div>
        <h2>LED 2</h2>
        <a href="/led2/on"><button class="button button-on">ON</button></a>
        <a href="/led2/off"><button class="button button-off">OFF</button></a>
      </div>
      <div>
        <h2>LED 3</h2>
        <a href="/led3/on"><button class="button button-on">ON</button></a>
        <a href="/led3/off"><button class="button button-off">OFF</button></a>
      </div>
      <div class="footer">
        © 2025 Erick_Systems - Group 5 (Ochola Emmanuel David, Lubangeyo Marvin, Achen Mercy, Auma Linda Grace, Jakuma Derrick, Amuge Charity, Muhumuza Benedicto, Gibayi Eric, Ojok Erick Mondoki, Okello Vincent)
      </div>
    </div>
  </body>
  </html>
  )=====";
  return html;
}

void setup() {
  // Initialize serial
  Serial.begin(115200);
  
  // Initialize LED pins
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // Define server routes
  server.on("/", []() {
    server.send(200, "text/html", getHTML());
  });

  server.on("/led1/on", []() {
    digitalWrite(led1, HIGH);
    server.send(200, "text/html", getHTML());
  });
  server.on("/led1/off", []() {
    digitalWrite(led1, LOW);
    server.send(200, "text/html", getHTML());
  });

  server.on("/led2/on", []() {
    digitalWrite(led2, HIGH);
    server.send(200, "text/html", getHTML());
  });
  server.on("/led2/off", []() {
    digitalWrite(led2, LOW);
    server.send(200, "text/html", getHTML());
  });

  server.on("/led3/on", []() {
    digitalWrite(led3, HIGH);
    server.send(200, "text/html", getHTML());
  });
  server.on("/led3/off", []() {
    digitalWrite(led3, LOW);
    server.send(200, "text/html", getHTML());
  });

  // Start server
  server.begin();
}

void loop() {
  server.handleClient();
}