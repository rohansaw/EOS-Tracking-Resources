# EOS-Tracking-Resources

This Repository contains material related to the "Tracking Technologien" project from the lecture "Embedded Operating Systems" in the winter-semester 2021/22. The project aims to compare different localization and communication technologies and is built up as follows:

#### Localization Technologies

- GPS
- Wifi Triangulation: The project [WiGLE.net](wigle.net) offers a database of wireless networks. This can be used to get geopositional data from scanned BSSIDs. The usage of wigle is free but with limited access to the api (only 5-7 request per day). We recommend to write an email to the [WiGLE admins](mailto:WiGLE-admin@WiGLE.net) to increase the amount of requests per day.
- GSM: GSM allows to track a device to an accuracy of up to 25m. However, multiple of our GSM modules were broken, therefore we were not able to implement this.
- Sigfox: The Sigfox network uses a number of proprietary transmissions towers which have a fixed position. From this a device can be located very roughly (identifying the city it is in). This service is directly included in the Sigfox subscription. We can also recommend to content the sigfox-provider as they gave out a free subscription for this project after asking.
- AirTag-like - FindMy-Network: Apples FindMy Network uses the huge mass of apple devices that already have location services turned on, in order to detect other devices that are passing by. Based on the location from multiple apple devices that received a signal from the device that should be located, the position of this device can be estimated. The device broadcasts its key via bluetooth low energy and the apple devices then upload their location to this key. The only problem in development here, is that we do not have a Mac available and can therefore not develop the backend, as only certified apple devices may access apples servers on which the location reports are stored.

#### Communication Technologies

- GSM: See above
- Sigfox: The Sigfox Network is a Low-Power Wan, allowing devices to send signals over a long range, while consuming only very little energy for every sent message. However, it only allows for 140 uplink and 4 downlink messages to be sent per day. In Germany Sigfox has a network-coverage of more than 90%.
- BLE + taking advantage of apples FindMy-Network (AirTag-like): See above.

#### Tradeoff: Energy Consumption vs. Accuracy

**Localization**
| Method             | Accuracy | Sleep Consumption | Get Location Consumption      |
|--------------------|----------|-------------------|-------------------------------|
| Wifi Triangulation | ~70m     | 12mA              | 122mA (2sec)                  |
| GPS                | ~5m      | 5mA               | 45mA (TTF can be up to 20min) |
| Sigfox             | ~8km     | 0.3uA             | 45mA (3sec)                   |
| GSM                | ~200m    | 1mA               | not able to measure           |

**Communication (Sending 12Byte)**
| Method    | Sleep Consumption | Send Message Consumption      | Cost                  |
|-----------|-------------------|-------------------------------|-----------------------|
| SigFox    | 0.3uA             | ~45mA                         | ~1???/month             |
| GSM  GPRS | 1mA               | ~450mA according to datasheet | ~6ctMB -> 12ct/month  |
| GSM -SMS  | 1mA               | ~450mA according to datasheet | ~5ct/SMS -> expensive |
| LoRaWan   | -                 | could be future work          | -                     |

#### Final Prototype
In our final prototype we used a arduino nano and modified the hardware to consume less power: We removed the led and voltage regulator and then used the sleep mode and disabled the analog-digital converter and brown-out detection. With this approach the consumption can be reduced to less than 1mA. We used the arduino nano, since in our observation the ESP32 devBoards that we had were not able to reach such a low power consumption as the arduino, even though accoring to the datasheet this should be possible.
