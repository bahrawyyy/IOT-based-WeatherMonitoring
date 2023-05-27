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

  


  
![WhatsApp Image 2023-05-22 at 23 11 17](https://github.com/bahrawyyy/IOT-based-WeatherMonitoring/assets/71684437/9d3e8aeb-3174-49c1-8b64-c2459c31633d)
![WhatsApp Image 2023-05-17 at 12 39 38](https://github.com/bahrawyyy/IOT-based-WeatherMonitoring/assets/71684437/c513f8aa-c94f-492d-b8f9-eceee8d9ae36)
![WhatsApp Image 2023-05-26 at 17 00 03](https://github.com/bahrawyyy/IOT-based-WeatherMonitoring/assets/71684437/120a9823-a3ed-41e8-8a92-e8941fc6fb6a)  
  
  

# Videos
- Here is a video of hardware running:  
https://drive.google.com/file/d/18gV9Qwgb22_uw9RDDLv9rGhjqO-2OSEZ/view?usp=sharing  
- A simple video that describes the project in more details:  
https://drive.google.com/file/d/1AA966coDbh1kisffIPblSRR4k5kUstOt/view?usp=sharing  
  
  


