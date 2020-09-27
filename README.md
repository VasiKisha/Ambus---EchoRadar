# Ambus - EchoRadar peripheral

## Components
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- SG90 MicroServo

## Connections
### HC-SR04
- HC-SR04:Vcc       Arduino:5V
- HC-SR04:Trig      Arduino:~3
- HC-SR04:Echo      Arduino:2
- HC-SR04:Gnd       Arduino:GND
### SG90
- SG90:PWM(orange)  Arduino:4
- SG90:+5V(red)     Arduino:5V
- SG90:GND(brown)   Arduino:GND

## Ambus Commands
|Command|Description                |
|:-----:|:-------------------------:|
| DEV?  | get device description    |
| FW?   | get firmware version      |
| An?   | get servo angle           |
| An    | set servo angle           |
| Dur?  | get duration of echo ping |
| Dis?  | get distance to obstacle  |

Device address: ECHO1
