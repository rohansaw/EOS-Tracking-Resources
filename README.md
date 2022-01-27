# EOS-Tracking-Resources

This Repository contains material related to the "Tracking Technologien" project from the lecture "Embedded Operating Systems" in the winter-semester 2021/22. The project aims to compare different localization and communication technologies and is built up as follows:

#### Localization Technologies

- GPS
- Wifi Triangulation
- GSM (optional)
- Sigfox: The Sigfox network uses a number of proprietary transmissions towers which have a fixed position. From this a device can be located very roughly (identifying the city it is in). This service is directly included in the Sigfox subscription. We can also recommend to content the sigfox-provider as they gave out a free subscription for this project after asking.
- AirTag-like - FindMy-Network: Apples FindMy Network uses the huge mass of apple devices that already have location services turned on, in order to detect other devices that are passing by. Based on the location from multiple apple devices that received a signal from the device that should be located, the position of this device can be estimated. The device broadcasts its key via bluetooth low energy and the apple devices then upload their location to this key. The only problem in development here, is that we do not have a Mac available and can therefore not develop the backend, as only certified apple devices may access apples servers on which the location reports are stored.

#### Communication Technologies

- GSM
- Sigfox: The Sigfox Network is a Low-Power Wan, allowing devices to send signals over a long range, while consuming only very little energy for every sent message. However, it only allows for 140 uplink and 4 downlink messages to be sent per day. In Germany Sigfox has a network-coverage of more than 90%. 
- BLE + taking advantage of apples FindMy-Network (AirTag-like): See above.

#### Tradeoff: Energy Consumption vs. Accuracy

ToDo: Insert table of values we measured

#### Final Prototype

ToDo: Combine best localization method with best communication method and add vibration-sensor

#### Further Resources:

- Learnings: link to doc