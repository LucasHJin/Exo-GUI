***GUI for Exo Software***

**Specification**
- **Motor**: brushless Eagle 8308
- **Driver (motor controller)**: ODrive S1

**Useful Documentation**
- [CAN Protocol](https://docs.odriverobotics.com/v/latest/manual/can-protocol.html)
- [CAN BUS guide](https://docs.odriverobotics.com/v/latest/guides/can-guide.html)
- [ODrive S1 Datasheet](https://docs.odriverobotics.com/v/latest/hardware/s1-datasheet.html)

**Important Note**
- On the ESP32, CAN is referred as **TWAI**. Use twai.h libaray to work with CAN.
- Always open the **firmware** projct in VS code directly, **not via the Exo_GUI folder**. Otherwise, VS code won't recognize the ESP-IDF libraries.
