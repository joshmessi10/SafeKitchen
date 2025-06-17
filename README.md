# 🛠️ Safe Kitchen: Smart Kitchen Alarm System (IoT-Based)


## 📘 Overview

**Safe Kitchen** is an IoT-based project designed to prevent gas leaks and fires in household kitchens. It integrates gas, flame, and temperature sensors with real-time monitoring via Node-RED and Ubidots, alerts through SMS using Vonage, and local data storage on a Raspberry Pi.

---

## 🔥 Why This Project?

Kitchen-related incidents remain a major cause of house fires and fatalities worldwide. Many of these are preventable with early detection systems. Common causes include:

- Leaving food unattended on stoves.
- Forgetting burners or ovens on.
- Using loose clothing near heat sources.
- Placing flammable objects near heat.

Despite warnings, accidents continue to rise. This project aims to build a smart, user-friendly, and low-cost system that detects early warning signs and alerts residents and emergency services promptly.

---

## 🎯 Project Objectives

### General Objective:
Develop a smart alarm system to prevent kitchen accidents caused by gas leaks and fire hazards.

### Specific Objectives:

- 🔍 Detect environmental changes in the kitchen using gas, flame, and temperature sensors.
- 📊 Display sensor data via a local dashboard and cloud platform (Node-RED and Ubidots).
- 🚨 Trigger alarms and send SMS notifications in case of gas or fire detection.
- ☁️ Enable cloud connectivity and mobile access for users.
- 💡 Maintain a low-cost and user-friendly design.

---

## 🧩 System Architecture

The system consists of the following components:

- **ESP32** microcontroller for sensor data acquisition.
- **Raspberry Pi** for data processing and dashboard control via Node-RED.
- **Sensors:** gas, flame, temperature.
- **Cloud integration** using MQTT and **Ubidots**.
- **Local storage** using SQLite and CSV export.
- **SMS alerts** via Vonage API.

### 📦 Block Diagram

```text
[ Gas Sensor ]             [ Flame Sensor ]            [ Temp Sensor ]
       \                         |                            /
        \                        |                           /
         \                       |                          /
                         [ ESP32 Microcontroller ]
                                |
                        [ Wi-Fi / MQTT Protocol ]
                                |
         -------------------------------------------------
        |                   |                           |
[ Raspberry Pi ]    [ Ubidots Cloud ]          [ Vonage SMS Alerts ]
        |
[ SQLite + CSV Storage ]

```

![SK1](https://github.com/user-attachments/assets/15efedb4-6e4b-4c93-b92e-ee0a96d04ccf)


### 📷 Example Screenshots:
Node-RED UI with real-time data.
![SK2](https://github.com/user-attachments/assets/1940c17c-8d26-434f-980e-75451d6371e3)

Ubidots cloud dashboard.
![SK3](https://github.com/user-attachments/assets/30daa72c-97f6-439b-aa7a-19948a8b457b)

SQLite database.
![SK4](https://github.com/user-attachments/assets/5f142926-f4b1-4358-80db-091ec4d56b94)

SMS alert confirming fire/gas detection.
![SK5](https://github.com/user-attachments/assets/46b0ff95-5749-4fda-831e-5ad2e34d9773)

### 🧠 Conclusions

The proposed system was successfully designed and built with a web socket interface and Wi-Fi communication.

Sensor integration and MQTT communication were validated.

The system shows promise for low-cost domestic safety solutions.

Future improvements may include:

- Direct ESP32-to-Ubidots MQTT integration.

- Evaluation of alternative microcontrollers and protocols.

- Testing additional sensors for accuracy and cost-efficiency.

### 👥 Team Members:

- [Josh Lopez](https://github.com/joshmessi10)
