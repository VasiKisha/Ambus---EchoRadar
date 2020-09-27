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
		
		void serialEventHandler();				//um�stit do serialEvent() - star� se o p��jem bajt�, rozpozn�v�n� SOP a EOP, anal�zu p�ijat� zpr�vy, kontrolu CRC a kontrolu adresy
		boolean dataReceived();					//True = nov� zpr�va, False = nen� nov� zpr�va
		String getCommand();					//vr�t� command z p�ijat�ho paketu
		String getData();						//vr�t� data z p�ijat�ho paketu
		void notacknowledge();					//nepotvrzuji p��jem zpr�vy
		void acknowledge(String answer = "");	//potvrzuji p�ijet� zpr�vy, voliteln� lze p�ipojit data;
		
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