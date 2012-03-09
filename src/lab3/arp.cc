#include "compiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "system.h"
}

#include "iostream.hh"
#include "arp.hh"
#include "ip.hh"

#define trace if(false) cout

ARPInPacket::ARPInPacket(byte* theData, udword theLength, InPacket* theFrame) : InPacket(theData, theLength, theFrame)
{
}

void ARPInPacket::decode()
{	
	ARPHeader * packet = (ARPHeader*) myData;
	
	if (packet->targetIPAddress == IP::instance().myAddress()) {
		trace << "This is for me" << endl;
		
		mySenderEthAddress = packet->senderEthAddress;
		mySenderIPAddress = packet->senderIPAddress;
		
		uword hoffs = myFrame->headerOffset();

		byte* temp = new byte[myLength + hoffs];
		byte* replyData = temp + hoffs;
		
		this->answer(replyData, myLength);
	}
}

void ARPInPacket::answer(byte* theData, udword theLength)
{
	ARPHeader * packet = (ARPHeader*) theData;

	packet->hardType = 0x0100;
	packet->protType = 0x0008;
	packet->hardSize = 0x06;
	packet->protSize = 0x04;
	packet->targetEthAddress = mySenderEthAddress;
	packet->targetIPAddress = mySenderIPAddress;
	packet->senderEthAddress = Ethernet::instance().myAddress();
	packet->senderIPAddress = IP::instance().myAddress();
	packet->op = 0x0200; // 2 for ARP reply, don't forget endianess

	myFrame->answer(theData, theLength);
}

uword ARPInPacket::headerOffset()
{
	return myFrame->headerOffset();
}
