***GUI for Exo Software***

**Specification**
- **Motor**: brushless Eagle 8308
- **Driver (motor controller)**: ODrive S1

**Documentation / References**
Always reference the below three sites:
- [CAN Protocol](https://docs.odriverobotics.com/v/latest/manual/can-protocol.html)
- [CAN BUS guide](https://docs.odriverobotics.com/v/latest/guides/can-guide.html)
- [ODrive S1 Datasheet](https://docs.odriverobotics.com/v/latest/hardware/s1-datasheet.html)

Some useful sites to read:
- [Closed Loop System Overview](https://v6.docs.ctr-electronics.com/en/latest/docs/api-reference/device-specific/talonfx/closed-loop-requests.html)
- [Basic PID and Profilling](https://v6.docs.ctr-electronics.com/en/latest/docs/api-reference/device-specific/talonfx/basic-pid-control.html)
- [CAN Bus Explained](https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial)

**Important Note**
- On the ESP32, CAN is referred as **TWAI**. Use twai.h libaray to work with CAN.
- Always open the **firmware** projct in VS code directly, **not via the Exo_GUI folder**. Otherwise, VS code won't recognize the ESP-IDF libraries.
