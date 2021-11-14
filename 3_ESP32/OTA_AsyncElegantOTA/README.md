# OTA (Over The Air) AsyncElegantOTA

## Links

- Libraries

  - [AsyncElegantOTA](https://github.com/ayushsharma82/AsyncElegantOTA)
  - [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
  - [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)

- Original Blog

  - [ESP32 OTA (Over-the-Air) Updates – AsyncElegantOTA using Arduino IDE](https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/)

> If you can't find any of the libraries above, download them as `.zip` file and manually upload to your Arduino IDE

## Configuration

Create a new file called `env.h` in the same directory of your main file.

> **ATTENTION:** add this file to your `.gitignore`, we are going to store our credentials

```C++
  const char* WIFI_NAME = "your_wifi_name";
  const char* WIFI_PASSWORD = "your_wifi_password";
```

## Code

```C++
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <AsyncElegantOTA.h>
  #include "env.h";

  AsyncWebServer server(80);

  void setup(void) {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WIFI_NAME);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Hi! I am ESP32.");
    });

    AsyncElegantOTA.begin(&server);
    server.begin();
    Serial.println("HTTP server started");
  }

  void loop(void) {
  }
```
