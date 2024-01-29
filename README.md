# ESP32 Wake-On-Lan server

This project provides a simple web-based Wake-on-LAN (WOL) controller to remotely wake up your computer. It is implemented using the ESPAsyncWebServer library on an ESP32 or ESP8266 microcontroller.

## Features

- Web interface for triggering Wake-on-LAN.
- Basic authentication to secure the controller access.
- Reconnects to WiFi if the connection is lost.

## Prerequisites

Before you begin, ensure you have the following:

- Arduino IDE installed.
- ESPAsyncWebServer library installed.
- WiFi and Wake-on-LAN credentials (SSID, password, and MAC address).

## Getting Started

1. Clone or download the project.
2. Open the Arduino IDE.
3. Install the required libraries (`IPAddress`, `ESPAsyncWebServer`, `WiFi`, `WiFiUdp`, `WakeOnLan`).
4. Replace placeholders in the code with your WiFi and Wake-on-LAN credentials.

```cpp
const char* ssid = "Your-SSID";
const char* password = "Your-WiFi-Password";
const char* MACAddress = "Your-Computer-MAC-Address";
const char* http_username = "Your-Username";
const char* http_password = "Your-Password";
```

5. Set the static IP address for your ESP device if needed:

```cpp
IPAddress staticIP(192, 168, 1, 155);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WiFi.config(staticIP, gateway, subnet);
```

6. Upload the code to your ESP device.

## Usage

1. Power up your ESP device.
2. Connect to the WiFi network.
3. Open a web browser and navigate to the IP address displayed in the Serial Monitor.
4. Log in using the specified username and password.
5. Click the "Wake On LAN" button to remotely wake up your computer.
6. Check the status or go back to the home page.

## Customization

- You can customize the HTML and CSS in the code to match your preferences.
- Adjust the check interval in the `loop` function for WiFi reconnection.

```cpp
const unsigned long checkInterval = 300000; // Check every 5 minutes
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [WakeOnLan](https://github.com/a7md0/WakeOnLan)

Feel free to contribute, report issues, or suggest improvements!

