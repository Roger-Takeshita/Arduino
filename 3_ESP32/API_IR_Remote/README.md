<h1 id='contents'>Table of Contents</h1>

- [API IR REMOTE](#api-ir-remote)
  - [Environment Variables](#environment-variables)
  - [Components](#components)
  - [Configuration](#configuration)

# API IR REMOTE

## Environment Variables

[Go Back to Contents](#contents)

- Create a new file in the same folder of your arduino app.

  ```Bash
    touch env.h
  ```

- In `env.h`

  ```C++
    const char* WIFI = "";
    const char* WIFI_PASSWORD = "";
    const char* JWT_TOKEN = "";
    const char* BACKEND_URL = "";
    const char* BOARD_NAME = "WEMOS Lolin32 Lite";
  ```

## Components

[Go Back to Contents](#contents)

- ESP32 Lolin32 Lite

  ![](https://i.imgur.com/RleJMlf.png)

- Mini Remote

  ![](https://i.imgur.com/yaZGJFB.png)

- IR Sensor

  ![](https://i.imgur.com/fky0HwQ.png)

## Configuration

[Go Back to Contents](#contents)

- IR Sensor
  ![](https://i.imgur.com/Th4PZRp.jpg)

  - Signal connects to port: `35`

- Buttons

  - `0-9` will make a `GET` request
  - `10-16` will make a `POST` request

  ```C++
    BTN_PRESS = 0;  // NUMBER 0
    BTN_PRESS = 1;  // NUMBER 1
    BTN_PRESS = 2;  // NUMBER 2
    BTN_PRESS = 3;  // NUMBER 3
    BTN_PRESS = 4;  // NUMBER 4
    BTN_PRESS = 5;  // NUMBER 5
    BTN_PRESS = 6;  // NUMBER 6
    BTN_PRESS = 7;  // NUMBER 7
    BTN_PRESS = 8;  // NUMBER 8
    BTN_PRESS = 9;  // NUMBER 9
    BTN_PRESS = 10; // *
    BTN_PRESS = 11; // #
    BTN_PRESS = 12; // UP
    BTN_PRESS = 13; // DOWN
    BTN_PRESS = 14; // LEFT
    BTN_PRESS = 15; // RIGHT
    BTN_PRESS = 16; // OK
  ```
