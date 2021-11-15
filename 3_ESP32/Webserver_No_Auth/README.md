# Webserver Server No Auth

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
  #include "env.h";

  WiFiServer server(80);

  void setup() {
      Serial.begin(115200);
      pinMode(0, OUTPUT);
      WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
      }

      Serial.print("");
      Serial.println("WiFi connected.");
      Serial.println(WIFI_NAME);
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());

      server.begin();
  }

  void loop() {
   WiFiClient client = server.available();

    if (client) {
      String currentLine = "";

      while (client.connected()) {
        if (client.available()) {
          char c = client.read();

          if (c == '\n') {
            if (currentLine.length() == 0) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();
              client.print("OK");
              client.println();
              break;
            } else {
              currentLine = "";
            }
          } else if (c != '\r') {
            currentLine += c;
          }

          if (currentLine.endsWith("GET /H")) {
            digitalWrite(0, HIGH);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("High Received");
            client.println();
            break;
          } else if (currentLine.endsWith("GET /L")) {
            digitalWrite(0, LOW);
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Low Received");
            client.println();
            break;
          }
        }
      }

      client.stop();
    }
  }
```
