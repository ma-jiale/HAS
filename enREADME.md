<h1 align="center">HAS: A Simple Home Assistant System</h1>
<div align="center">
<a href="https://github.com/ma-jiale/HAS/stargazers"><img src="https://img.shields.io/github/stars/ma-jiale/HAS" alt="Stars Badge"/></a>
<a href="https://github.com/ma-jiale/HAS/network/members"><img src="https://img.shields.io/github/forks/ma-jiale/HAS" alt="Forks Badge"/></a>
<a href="https://github.com/ma-jiale/HAS/pulls"><img src="https://img.shields.io/github/issues-pr/ma-jiale/HAS" alt="Pull Requests Badge"/></a>
<a href="https://github.com/ma-jiale/HAS/issues"><img src="https://img.shields.io/github/issues/ma-jiale/HAS" alt="Issues Badge"/></a>
<a href="https://github.com/ma-jiale/HAS/graphs/contributors"><img alt="GitHub contributors" src="https://img.shields.io/github/contributors/ma-jiale/HAS?color=2b9348"></a>
<a href="https://github.com/ma-jiale/HAS/blob/master/LICENSE"><img src="https://img.shields.io/github/license/ma-jiale/HAS?color=2b9348" alt="License Badge"/></a>
<a href="https://github.com/ma-jiale/HAS/blob/main/README.md"><img src="https://img.shields.io/static/v1?label=&labelColor=505050&message=Chinese README 中文自述文件&color=%230076D6&style=flat&logo=google-chrome&logoColor=green" alt="website"/></a>
<i>Like this project? Please consider giving it a Star ⭐️ to help improve!</i>
</div>

> This project is an assignment from the "Interactive Technology" course. The task was to design and implement a smart home user interface that can collect temperature and humidity data or control a light. I named it HAS, which stands for "A Simple Home Assistant System." The project primarily uses the Arduino microcontroller to simulate actual smart home control, Flask as the lightweight web framework for building the web server (Life is short, I use Python!), Figma for designing the frontend interface, and HTML/CSS/JavaScript (the "Frontend Trio") + Bootstrap for building the frontend web page. Due to my limited capabilities, some parts of the work were done with the help of ChatGPT. If you notice any errors or areas for improvement, please feel free to offer your suggestions.

### Updates

#### 24.12.7 Update

- Created repository
- Added README.md
- Added circuit design
- Added firmware code

### 1. Project File Description

### 2. Circuit Design

The circuit design initially plans to use the Arduino microcontroller to simulate smart home control for a typical bedroom.

- Use a diode to simulate a ceiling light.
- Use a servo to simulate an electric curtain.
- Use a temperature and humidity sensor to simulate a thermometer.
- Use a DC motor to simulate a fan.
- More to be added...

#### 2.1 Circuit Design Diagram

![image-20241207210928744](images/image-20241207210928744.png)

#### 2.2 Simulation Wiring Diagram

![image-20241207210901251](images/image-20241207210901251.png)

#### 2.3 Physical Wiring Reference

![87394059b209aa6c3c10b5a23129b94](images/87394059b209aa6c3c10b5a23129b94.jpg)

#### 2.4 Microcontroller Selection

Currently, I am using the Arduino Uno3, as Arduino has a large number of pre-packaged third-party libraries, making it easy to get started.

In the future, I plan to replace it with the ESP32, which has Bluetooth and Wi-Fi capabilities, enabling wireless data transmission.

For an Arduino beginner's guide, you can refer to [Tai Chi Maker – Arduino, AI, IoT applications, development, and learning resources](http://www.taichi-maker.com/)

#### 2.5 Temperature and Humidity Sensor Selection

I have selected the DHT11 sensor for the temperature and humidity measurement.

![image-20241207213854992](images/image-20241207213854992.png)
Model: Humidity Sensor DHT11
Operating Voltage: 3-5.5V
Temperature Measurement Range: 0°C ~ 50°C
Temperature Measurement Accuracy: ±2°C
Temperature Resolution: 1°C
Humidity Measurement Range: 20% ~ 90% (0~50°C MAX)
Humidity Measurement Accuracy: ±5%
Humidity Resolution: 1% RH

Pin Definitions:
- Pin 1 (VDD): Power supply 3-5.5VDC
- Pin 2 (DATA): Serial data, single-wire
- Pin 3 (NC): No connection, leave floating
- Pin 4 (GND): Ground, negative power

Dimension Diagram:

![image-20241207213931250](images/image-20241207213931250.png)

Reference Circuit Diagram:

![image-20241207214011149](images/image-20241207214011149.png)

### 3. Software Architecture

#### 3.1 Firmware Code

The firmware code is stored in the [control_and_recieve_data](Software/control_and_recieve_data) directory. You can upload it to the Arduino Uno3 using the Arduino IDE.

### 4. Web Design Description

