# Arduino

Arduino Projects - Arduino Nano / ESP8266 / ESP32

Boards Manager

- ESP8266
  - [https://arduino.esp8266.com/stable/package_esp8266com_index.json](https://arduino.esp8266.com/stable/package_esp8266com_index.json)
- ESP32
  - [https://dl.espressif.com/dl/package_esp32_index.json](https://dl.espressif.com/dl/package_esp32_index.json)

```Bash
  https://arduino.esp8266.com/stable/package_esp8266com_index.json, https://dl.espressif.com/dl/package_esp32_index.json
```

## Drivers

- [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

VCP Drivers Features and Benefits
The CP210x USB to UART Bridge Virtual COM Port (VCP) drivers are required for device operation as a Virtual COM Port to facilitate host communication with CP210x products. These devices can also interface to a host using the direct access driver.

These drivers are static examples detailed in Application Note 197: The Serial Communications Guide for the CP210x.

The CP210x Manufacturing DLL and Runtime DLL have been updated and must be used with v 6.0 and later of the CP210x Windows VCP Driver. Application Note Software downloads affected are AN144SW.zip, AN205SW.zip and AN223SW.zip. If you are using a 5.x driver and need support you can download Legacy OS Software.

### Python Error

- [Deprecation of Python 2. Solution](https://github.com/espressif/arduino-esp32/issues/4717#issuecomment-1070801525)
- [exec: "python": executable file not found in $PATH on Arduino IDE](https://stackoverflow.com/questions/71143707/exec-python-executable-file-not-found-in-path-on-arduino-ide)

```Bash
  exec: "python": executable file not found in $PATH
  Error compiling for board ESP32 Dev Module.
```

```Bash
  sed -i -e 's/=python /=python3 /g' ~/Library/Arduino15/packages/esp32/hardware/esp32/*/platform.txt
```
