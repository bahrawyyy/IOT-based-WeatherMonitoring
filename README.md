# IOT-based-WeatherMonitoring
WeatherSense is an IoT-based weather monitoring project that utilizes embedded systems and sensors to gather weather data. This repository contains the source code and documentation needed to implement the project and set up a comprehensive weather monitoring system.

# Overview
The WeatherSense project focuses on collecting weather data from sensors such as DHT11 (temperature and humidity), MQ135 (air quality), and a rain sensor. The data collected from these sensors is transmitted to a NodeMCU development board via UART communication, following a specific protocol designed for secure and efficient data transmission.

The core functionality of the project is centered around the NodeMCU, which acts as a gateway device. It receives the sensor data from the connected sensors and interfaces with them using appropriate libraries. The NodeMCU then leverages its networking capabilities to transmit the collected weather data to two destinations: Firebase and the Blynk IoT platform.

# Features  
- Integration with DHT11, MQ135, and rain sensor for accurate weather data collection
- UART communication protocol for secure and efficient data transmission to NodeMCU
- Data transmission from NodeMCU to Firebase for reliable storage and easy data retrieval
- Integration with Blynk IoT platform for real-time weather data monitoring and control
- User-friendly Blynk mobile application and web dashboard for visualization and interaction  
  
  


