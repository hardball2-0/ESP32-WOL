//Pedro Andrade

#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>

// Replace with your credentials
const char* ssid = "SSID";
const char* password = "Wifi-password";
const char* MACAddress = "MAC-adress";

// Set up WiFiUDP to send WOL messages
WiFiUDP UDP;
WakeOnLan WOL(UDP);

const char* http_username = "username";
const char* http_password = "password";

AsyncWebServer server(80);

void wakeMyPC() {
    WOL.setRepeat(3, 100);
    WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
    WOL.sendMagicPacket(MACAddress);
}

void setup() {
    Serial.begin(115200);

    Serial.print("MAC address of ESP32: ");
    Serial.println(WiFi.macAddress());

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Route for root / web page with authentication
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        if(!request->authenticate(http_username, http_password))
            return request->requestAuthentication();
            
        String content = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Wake Up</title>
  <style>
    body {
      background-color: #e0e0e0; /* Grey background color */
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
      margin: 0;
    }

    #buttonContainer {
      text-align: center;
    }

    #wakeButton {
      background-color: #3498db; /* Blue button color */
      color: #fff; /* White text color */
      font-size: 20px;
      padding: 15px 30px;
      border: none;
      border-radius: 5px;
      cursor: pointer;
    }

    #title {
      margin-top: 20px;
      font-size: 24px;
    }
  </style>
</head>
<body>

  <div id="buttonContainer">
    <button id="wakeButton" onclick="window.location='/wake'">Wake On LAN</button>
  </div>

  <div id="title">Click the button to wake up!</div>

</body>
</html>
)rawliteral";

        request->send(200, "text/html", content);
    });

    // Route for /wake to trigger Wake-on-LAN
    server.on("/wake", HTTP_GET, [](AsyncWebServerRequest *request){
        if(!request->authenticate(http_username, http_password))
            return request->requestAuthentication();
            
        wakeMyPC();

        String content = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Wake Up</title>
  <style>
    body {
      background-color: #e0e0e0; /* Grey background color */
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
      margin: 0;
    }

    #buttonContainer {
      text-align: center;
    }

    #title {
      margin-top: 20px;
      font-size: 24px;
    }
  </style>
</head>
<body>

  <div id="buttonContainer">
    <p>Computer is turning on...</p>
    <p><a href="/"><button>Back to Home</button></a></p>
  </div>

</body>
</html>
)rawliteral";

        request->send(200, "text/html", content);
    });

    server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(401);
    });

    server.begin();
}

void loop() {
    // Check Internet connection every 5 minutes (300,000 milliseconds)
    static unsigned long lastCheckTime = 0;
    const unsigned long checkInterval = 300000;

    unsigned long currentMillis = millis();

    // Perform the check every 5 minutes
    if (currentMillis - lastCheckTime >= checkInterval) {
        lastCheckTime = currentMillis;

        // Check if not connected to WiFi
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi not connected. Reconnecting...");

            // Attempt to reconnect to WiFi
            WiFi.begin(ssid, password);

            // Wait for the connection
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }

            // Print local IP address after successful reconnection
            Serial.println("");
            Serial.println("WiFi reconnected.");
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
        }
    }

    // Other code in your loop can go here

    // Delay to avoid flooding the network
    delay(1000);
}

