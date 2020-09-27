/*
 * ambus.h
 *
 * Created: 02.07.2016 9:15:07
 *  Author: vlast
 */ 

#ifndef AMBUS_H_
#define AMBUS_H_

class AMBUS
{
	public:	
		AMBUS(String myAddress);
		
		void serialEventHandler();				//umístit do serialEvent() - stará se o pøíjem bajtù, rozpoznávání SOP a EOP, analýzu pøijaté zprávy, kontrolu CRC a kontrolu adresy
		boolean dataReceived();					//True = nová zpráva, False = není nová zpráva
		String getCommand();					//vrátí command z pøijatého paketu
		String getData();						//vrátí data z pøijatého paketu
		void notacknowledge();					//nepotvrzuji pøíjem zprávy
		void acknowledge(String answer = "");	//potvrzuji pøijetí zprávy, volitelnì lze pøipojit data;
		
	private:
		boolean receiving;						//receinving flag
		boolean dataReady;						//data ready flag
		
		String address;
		String command;
		String data;
		String crc;
		String deviceAddress;
		String dataPacket;
		
		void stringParser();					//analyzuje dataPacket
		char checksum(String data, unsigned int count);
};

#endif /* AMBUS_H_ */