# 2E10-Autonomous-Buggy
Arduino based autonomous line-following buggy featuring sensor-based obstacle detection and navigation.

## Overview
This project involves the development of an autonomous buggy using an Arduino Uno R4 Wi-Fi. The buggy follows a track using infrared (IR) sensors, detects obstacles using an ultrasonic sensor, and regulates its movement using wheel encoders and PID control.

The system also supports wireless communication with a Processing-based graphical user interface (GUI), allowing the user to start and stop the buggy, switch between control modes, adjust the reference speed, and monitor telemetry data.

## Features
Line Following: Uses left and right IR sensors to detect the track and control steering.
Obstacle Detection: Uses an ultrasonic sensor to measure the distance to objects ahead and stop when an obstacle is too close.
PID Speed Control: Adjusts motor PWM output to regulate the buggy's speed based on a user-defined reference speed.
Distance-Based Control: Uses ultrasonic distance measurements and PID control to maintain a target distance from an object.
Wheel Encoder Feedback: Tracks wheel rotations to calculate speed and distance travelled.
Wireless Communication: Communicates with a Processing GUI over Wi-Fi.
Real-Time Monitoring: Displays speed, reference speed, obstacle distance, total distance travelled, and control mode.
Motor Speed Calibration: Applies a scaling factor to compensate for differences between the left and right motors.
Responsive Steering: Optimises sensor polling and reduces unnecessary serial output to improve responsiveness at corners.

## Hardware Components
Arduino Uno R4 Wi-Fi
Two DC drive motors
H-bridge motor driver
Left and right infrared sensors
Ultrasonic distance sensor
Wheel encoders
Battery pack
Robotic buggy chassis and wheels

## Software and Technologies
Arduino C/C++
Arduino IDE
Processing GUI
Wi-Fi communication
PID control
Pulse Width Modulation (PWM)
Interrupts for wheel encoder pulse counting
