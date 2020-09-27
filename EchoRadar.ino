//Device description
#define DEVICE "Echo Radar"
//Firmware version
#define FIRMWARE "ver. 1.0"

#include "Echo.h"
#include "ambus.h"

#define ECHOPIN			2
#define TRIGPIN			3
#define SERVOPIN		4
#define MEAS_INTERVAL	30

//Device address
AMBUS ambus("ECHO1");
ECHO echo;

unsigned long previousMillis;
unsigned long currentMillis;
String stringTemp;
int intTemp;
boolean bTemp;

void setup()
{
	Serial.begin(115200);
	pinMode(ECHOPIN, INPUT);
	pinMode(TRIGPIN, OUTPUT);
	pinMode(SERVOPIN, OUTPUT);
	echo.begin(SERVOPIN, TRIGPIN, ECHOPIN);
}

void loop()
{
	currentMillis = millis();

	if (ambus.dataReceived())
	{
		if (ambus.getCommand() == "DEV?")
		{
			ambus.acknowledge(DEVICE);
		}
		else if (ambus.getCommand() == "FW?")
		{
			ambus.acknowledge(FIRMWARE);
		}
		else if (ambus.getCommand() == "An")
		{
			stringTemp = ambus.getData();
			intTemp = stringTemp.toInt();
			bTemp = echo.setAngle(intTemp);
			if (bTemp) ambus.acknowledge(String(intTemp));
			else ambus.notacknowledge();
		}
		else if (ambus.getCommand() == "An?")
		{
			ambus.acknowledge(String(echo.getAngle()));
		}
		else if (ambus.getCommand() == "Dur?")
		{
			ambus.acknowledge(String(echo.getDuration()));
		}
		else if (ambus.getCommand() == "Dis?")
		{
			ambus.acknowledge(String(echo.getDistance()));
		}
		else
		{
			ambus.notacknowledge();
		}
	}

	if (currentMillis - previousMillis >= MEAS_INTERVAL)
	{
		previousMillis = currentMillis;
	}
}

void serialEvent()
{
	ambus.serialEventHandler();
}