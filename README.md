
# DASH-BOARD-DESIGN-USING-CAN BUS
<h1 align="center">🚗DASH-BOARD-DESIGN-USING-CAN BUS</h1>

## 📖 **Overview**

The **DASH-BOARD-DESIGN-USING-CAN BUS** is an embedded systems project developed using the **LPC2129 ARM7 Microcontroller** and the **Controller Area Network (CAN) Protocol**.

This project demonstrates communication between multiple Electronic Control Units (ECUs) over a CAN Bus to monitor and display vehicle parameters such as:

- 🔋 Fuel Status
- 🌡️ Engine Temperature
- 🚦 Indicator Status

The system provides real-time monitoring through an LCD display and showcases distributed embedded system communication.

---

## 🎯 Project Objective

To design and develop a Dash Board Design Using CAN Bus that acquires, decodes, and displays real-time data from multiple ECUs, enabling effective monitoring of key vehicle parameters through an embedded display.

---

## ✨ Features

✅ Real-time CAN Communication

✅ Multi-Node Architecture

✅ Engine Temperature Monitoring

✅ Fuel Percentage Monitoring

✅ Indicator Control via CAN

✅ LCD-Based Status Display

✅ Interrupt-Based Event Handling

✅ ADC-Based Fuel Simulation

---

## 🏗️ System Architecture

### 🖥️ Main Node

- Reads engine temperature from DS18B20 sensor
- Displays temperature on LCD
- Receives fuel percentage from Fuel Node
- Sends indicator commands to Indicator Node
- Displays battery and indicator status

### 🔋 Fuel Node

- Monitors Fuel condition
- Uses Fuel Guage to simulate Fuel Percentage
- Converts voltage into fuel percentage (0–100%)
- Sends fuel status over CAN Bus

### 🚦 Indicator Node

- Receives commands from Main Node
- Controls 8 LEDs
- Displays left and right indicator patterns
- Implements scrolling LED effects

---
---

## 🛠️ Hardware Requirements

- LPC2129 ARM7 Microcontroller
- MCP2551 CAN Transceiver
- DS18B20 Temperature Sensor
- LCD Display
- Fuel Guage
- LEDs
- Push Buttons / Switches
- CAN Bus Connections

---

## 💻 Software Requirements

- Embedded C
- Keil uVision IDE
- Flash Magic

---

## 🔧 Technologies Used

- ARM7 LPC2129 Architecture
- Embedded C Programming
- CAN Protocol
- GPIO Interfacing
- ADC Interfacing
- External Interrupts
- LCD Interfacing
- DS18B20 Sensor Interfacing

---
### 🔄Block Diagram

<img width="1213" height="790" alt="image" src="https://github.com/Sudheer-1402/Dash-Board-Design-Using-CAN-Bus/blob/main/1528a4ed-3430-4f4f-8a64-079b5b83467a.png?raw=true" />

----
## ⚙️ Implementation Sequence

### 1️⃣ LCD Verification

- Interface LCD with LPC2129
- Display characters, strings, and integers

### 2️⃣ Switch Interfacing

- Interface active-low switches
- Display switch status on LCD

### 3️⃣ Temperature Monitoring

- Interface DS18B20 Sensor
- Read and display engine temperature

### 4️⃣ ADC Testing

- Connect potentiometer to ADC channel
- Display ADC value on LCD

### 5️⃣ External Interrupt Testing

- Configure EINT0 and EINT1
- Verify interrupt generation

### 6️⃣ CAN Communication Testing

- Configure CAN Controller
- Verify CAN transmission and reception

### 7️⃣ Node Development

- Develop Main Node
- Develop Fuel Node
- Develop Indicator Node

### 8️⃣ System Integration

- Connect all nodes through CAN Bus
- Test complete vehicle monitoring system

---

## 📂 Project Folder Structure

```text
Multi-ECU-Vehicle-Monitoring-Using-CAN/
│
├── Main_Node/
│ ├── main.c
│ ├── can.c
│ ├── lcd.c
│ └── ds18b20.c
│
├── Indicator_Node/
│ ├── indicator.c
│ └── can.c
│
├── Fuel_Node/
│ ├── fuel.c
│ └── adc.c
│
├── Docs/
│ ├── block_diagram.png
│
└── README.md
```
----

### Output

The LCD displays:

🌡️ Engine Temperature : XX °C

🔋 Fuel Level : XX %

🚦 Indicator Status :
LEFT / RIGHT / OFF

## 📸 Project Output

### Dashboard

<img width="3113" height="3000" alt="IMG_0671" src="https://github.com/Sudheer-1402/Dash-Board-Design-Using-CAN-Bus/blob/main/WhatsApp%20Image%202026-09-15%20at%2022.39.51%20(1).jpeg?raw=true" />

### Complete Setup

<img width="3113" height="2260" alt="IMG_0673" src="https://github.com/Sudheer-1402/Dash-Board-Design-Using-CAN-Bus/blob/main/setup.jpeg?raw=true" /> 
 
---- 
 
## 🚀 Applications 
 
- Automotive Embedded Systems 
- Vehicle Diagnostics 
- ECU Communication Systems 
- CAN-Based Industrial Automation 
- Vehicle Health Monitoring 
- Smart Transportation Systems 
- Distributed Embedded Networks 
---- 
## 🎓 Learning Outcomes 
 
- Embedded C Programming 
- CAN Protocol Implementation 
- LPC2129 ARM7 Architecture 
- ADC and GPIO Interfacing 
- Interrupt Handling 
- Sensor Integration 
- Multi-ECU Communication 
- Real-Time Embedded System Design 
 
----- 
 
## 👨‍💻 Project By 
 
Vijay Durga Gundubilli
 
B.Tech – Electrical and Electronics Engineering 
 
Vector India Major Project 
 
Embedded Systems | CAN | LPC2129 replace the blockdiagram image into this image
