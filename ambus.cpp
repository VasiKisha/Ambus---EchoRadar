/*
 * ambus.cpp
 *
 * Created: 02.07.2016 9:13:05
 *  Author: vlast
 */ 

#include <Arduino.h>
#include "ambus.h"

#define AMBUS_DEBUG

#define MASTER_ADDRESS "MASTER"

//PACKET DEFINITIONS
#define START_OF_PACKET	'$'
#define SEPARATOR		';'
#define END_OF_PACKET	'\n'
#define ADDRESS_SIZE	8
#define COMMAND_SIZE	8
#define DATA_SIZE		32
#define CRC_SIZE		1
#define PACKET_SIZE		ADDRESS_SIZE + COMMAND_SIZE + DATA_SIZE + CRC_SIZE + 5

AMBUS::AMBUS(String myAddress)
{
	dataPacket.reserve(PACKET_SIZE);
	address.reserve(ADDRESS_SIZE);
	command.reserve(COMMAND_SIZE);
	data.reserve(DATA_SIZE);
	crc.reserve(CRC_SIZE);
		
	deviceAddress = myAddress;
	dataPacket = "";
	address = "";
	command = "";
	data = "";
	crc = "";
		
	receiving = false;
	dataReady = false;
}

void AMBUS::serialEventHandler()
{
	//pokud data nejsou pøeètená tak nepøijímat další
	if(dataReady == true) return;
	
	//naèíst znak z linky
	char inChar = (char)Serial.read();
	
	if(receiving == false)		//ještì nejsem v pøijímacím módu
	{
		if(inChar == START_OF_PACKET)
		{
			receiving = true;
			dataPacket = "";
			dataPacket += inChar;
			return;
		}
	}
	else						//pøijímací mód
	{
		if(inChar == START_OF_PACKET) //detekován nový SOP
		{
			dataPacket = "";
		}
		dataPacket += inChar;
		if(dataPacket.length() >= PACKET_SIZE) //pøekroèena maximální délka zprávy
		{
			receiving = false;
			return;
		}
		if(inChar == END_OF_PACKET)	//detekován EOP
		{
			stringParser();			//analýza zprávy
			if(crc[0] != checksum( dataPacket , dataPacket.length()-1-CRC_SIZE ) ) //kontrola checksum
			{
				#ifdef AMBUS_DEBUG
				Serial.print("CRC NOT MATCH: ");
				Serial.println(checksum( dataPacket , dataPacket.length()-(1+CRC_SIZE) ));
				#endif
				address = "";
				command = "";
				data = "";
				crc = "";
				receiving = false;
				return;
			}
			if(address != deviceAddress)	//kontrola adresy
			{
				#ifdef AMBUS_DEBUG
				Serial.println("ADDRESS NOT MATCH: ");
				Serial.println(address);
				#endif
				address = "";
				command = "";
				data = "";
				crc = "";
				receiving = false;
				return;
			}
			dataReady = true;	//pokud se dostanu až jsem jsou data v poøádku a pøipravena k pøedání
			receiving = false;
		}
	}
}

boolean AMBUS::dataReceived()
{
	return dataReady;
}

String AMBUS::getCommand()
{
	return command;
}

String AMBUS::getData()
{
	return data;
}

void AMBUS::notacknowledge()
{
	#ifdef AMBUS_DEBUG
	Serial.println("NACK");
	#endif
	address = "";
	command = "";
	data = "";
	crc = "";
	dataReady = false;
}

void AMBUS::acknowledge(String answer)
{
	dataPacket = START_OF_PACKET;
	dataPacket += MASTER_ADDRESS;
	dataPacket += SEPARATOR;
	dataPacket += command;
	dataPacket += SEPARATOR;
	dataPacket += answer;
	if(answer != "") dataPacket += SEPARATOR;
	dataPacket += checksum(dataPacket, dataPacket.length());
	dataPacket += END_OF_PACKET;
	Serial.print(dataPacket);
	address = "";
	command = "";
	data = "";
	crc = "";
	dataReady = false;
}

void AMBUS::stringParser()
{
	unsigned int separatorCounter = 0;
	unsigned int i = 1;
	unsigned int j = 0;
	
	while(dataPacket[i] != END_OF_PACKET)
	{
		if(dataPacket[i] == SEPARATOR)
		{
			separatorCounter++;
			i++;
			j=0;
			continue;
		}
		
		switch (separatorCounter)
		{
			case 0:		//address
			if(j >= ADDRESS_SIZE) break;
			address += dataPacket[i];
			break;
			
			case 1:		//command
			if(j >= COMMAND_SIZE) break;
			command += dataPacket[i];
			break;
			
			case 2:		//data
			if(j >= DATA_SIZE) break;
			data += dataPacket[i];
			break;
			
			case 3:		//crc
			if(j >= CRC_SIZE) break;
			crc += dataPacket[i];			
			break;
			
			default:
			break;
		}
		
		i++;
		j++;
	}
	
	//pokud paket neobsahuje DATA
	if(separatorCounter == 2)
	{
		crc = data;
		data = "";	
	}
}

char AMBUS::checksum(String data, unsigned int count)
{
	int sum = 0;
	for(unsigned int i = 0; i < count; i++)
	{
		sum = (sum + data[i]) % 255;
	}
	if((char)sum == START_OF_PACKET)	return '\x1A';	//osetreni zakazaneho znaku
	if((char)sum == SEPARATOR)			return '\x1A';	//osetreni zakazaneho znaku
	else return (char)sum;
}
