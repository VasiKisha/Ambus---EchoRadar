//Copyright (c) 2020 VasiKisha
//All rights reserved.

//This source code is licensed under the MIT-style license found in the
//LICENSE file in the root directory of this source tree. 

/*
 * Echo.h
 *
 * Created: 16.07.2016 11:56:22
 *  Author: VasiKisha
 */ 

#include "Servo.h"

#ifndef ECHO_H_
#define ECHO_H_

class ECHO
{
    public:
        void begin(byte argServoPin, byte argTrigPin, byte argEchoPin);
        boolean setAngle(int angle);        // 1 - 179°
        int getAngle();
        unsigned int getDuration();
        unsigned int getDistance();
    private:
        Servo servo;
        byte servoPin;
        byte trigPin;
        byte echoPin;
};



#endif /* ECHO_H_ */
