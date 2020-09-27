/*
 * Echo.cpp
 *
 * Created: 16.07.2016 11:56:36
 *  Author: vlast
 */ 
#include <Arduino.h>
#include "Echo.h"

void ECHO::begin(byte argServoPin, byte argTrigPin, byte argEchoPin)
{
	servoPin = argServoPin;
	trigPin = argTrigPin;
	echoPin = argEchoPin;
	servo.attach(servoPin);
	servo.write(90);
}

boolean ECHO::setAngle(int angle)
{
	if (angle >= 180) return false;
	if (angle <= 0)	  return false;
	servo.write(angle);
	return true;
}

int ECHO::getAngle()
{
	return servo.read();
}

unsigned int ECHO::getDuration()	//returns sound travel duration in us
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin,HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin,LOW);

	return pulseIn(echoPin,HIGH,30000);
}

unsigned int ECHO::getDistance()
{
	return getDuration()*0.017;
}
