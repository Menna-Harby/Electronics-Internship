# Electronics-Internship
Learning-by-building: My ongoing journey through Arduino-based electronics, as part of a university Summer Internship

# 🌟 Smart Room Lighting System

## 📌 Objective

To design and implement an Arduino-based **smart lighting system** that:

- Automatically adjusts LED brightness based on ambient light.
- Allows manual control using a button.
- Implements debouncing for button reliability.
- Saves energy with an auto-timeout feature when no activity is detected.

---

## 🛠️ Components Used

| Component           | Quantity | Description                  | Cost    | Store Link |
|---------------------|----------|-------------------------------|---------|------------|
| Arduino Uno         | 1        | Microcontroller               | 400 EGP | [Link](https://mecha-tronx.com/product/arduino-uno-r3/) |
| LED                 | 1        | Output light source           | 0.50 EGP | [Link](https://mecha-tronx.com/product/led-5mm/) |
| Photoresistor (LDR) | 1        | Detects ambient light         | 15 EGP  | [Link](https://mecha-tronx.com/product/photo-resistor-sensor-ldr-7mm/) |
| 10kΩ Resistor       | 1        | For LDR voltage divider       | 3 EGP   |            |
| Push Button         | 1        | User input                    | 1 EGP   |            |
| 220Ω Resistor       | 1        | Current limit for LED         | 3 EGP   |            |
| Breadboard + Wires  | -        | For prototyping               | 12 EGP  | [Link](https://mecha-tronx.com/product/170pts-mini-breadboard-syb-170/) |

> 💰 **Total Cost: 440 EGP**

---

## 🔌 Circuit Diagram

🧠 **Wiring Summary**:

- **LDR Circuit**:
  - One leg to 5V
  - Other leg to A0 and GND via 10kΩ resistor
- **LED Circuit**:
  - Anode to PWM pin 9 through 220Ω resistor
  - Cathode to GND
- **Button Circuit**:
  - One leg to digital pin 2
  - Other leg to GND

---

## 💡 System Behavior Description

| Mode          | Trigger             | Behavior                                                                  |
|---------------|---------------------|---------------------------------------------------------------------------|
| Auto Mode     | Default state        | LED brightness adjusts with light via LDR                                 |
| Manual Mode   | Press button         | Cycles brightness: 25% → 50% → 75% → 100% → OFF                           |
| Debouncing    | In software          | Prevents false triggers from button bounces                               |
| Timeout       | 2 mins no activity   | Turns LED off to save energy                                              |
| Reactivation  | Press button         | Resumes last state and reactivates LED control                            |

---

