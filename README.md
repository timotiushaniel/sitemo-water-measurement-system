# sitemo-water-measurement-system
This is a college project to make an IoT simple project. This is a water measurement system by using NodeMCU, Blynk, and Telegram Bot.
The user will receive the notification via Telegram Bot and the user can check the real-time status by using Blynk app.

Water Measurement Documentation

Ultrasonic Sensor:
1. Ultrasonic Vcc  - Vin NodeMCU
2. Ultrasonic Trig - D4 NodeMCU
3. Ultrasonic Echo - D3 NodeMCU
4. Ultrasonic Gnd  - G NodeMCU

I2C_LCD Display:
1. I2C_LCD GND - G NodeMCU
2. I2C_LCD VCC - Vin NodeMCU
3. I2C_LCD SDA - D2 NodeMCU
4. I2C_LCD SDL - D1 NodeMCU

RED LED:
1. Katona (+) - D0 NodeMCU
2. Anoda (-)  - G NodeMCU

BLUE LED:
1. Anoda (+) - D5 NodeMCU
2. Katoda (-) - G NodeMCU

GREEN LED:
1. Anoda (+) - D6 NodeMCU
2. Katoda (-) - G NodeMCU

BUZZER:
1. Anoda (+) - D7 NodeMCU
2. Katoda (-) - G NodeMCU
