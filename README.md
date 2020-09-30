# Ambus - EchoRadar peripheral

## Components
- Arduino UNO
- HC-SR04 Ultrasonic Sensor
- SG90 MicroServo

## Connections
### HC-SR04
|HC-SR04|Arduino UNO|
|:-----:|:---------:|
| Vcc   | 5V        |
| Trig  | ~3        |
| Echo  | 2         |
| Gnd   | Gnd       |
### SG90
| SG90  |Arduino UNO|
|:------------:|:---------:|
| PWM (orange) | 4         |
| +5V (red)    | 5V        |
| GND (brown   | GND       |

## Ambus Commands
|Command|Description                |
|:-----:|:-------------------------:|
| DEV?  | get device description    |
| FW?   | get firmware version      |
| An?   | get servo angle           |
| An    | set servo angle           |
| Dur?  | get sound travel duration |
| Dis?  | get distance to obstacle  |

Device address: ECHO1

See [Ambus protocol description](https://github.com/VasiKisha/Ambus/blob/master/README.md) for more details.
