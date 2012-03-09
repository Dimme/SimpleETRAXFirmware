#include "compiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "system.h"
}

#include "iostream.hh"
#include "ip.hh"
#include "icmp.hh"

#define trace if(false) cout

IP::IP()
{
	myIPAddress = new IPAddress(130,235,200,101);
}

IP& IP::instance()
{
	static IP instance;
	return instance;
}

const IPAddress& IP::myAddress()
{
	return *myIPAddress;
}

IPInPacket::IPInPacket(byte* theData, udword theLength, InPacket* theFrame) : InPacket(theData, theLength, theFrame)
{	
}

void IPInPacket::decode()
{
	IPHeader * header = (IPHeader*) myData;
	
	if (header->protocol == 0x01 /* ICMP packet */) {
		trace << "ICMP Packet in!" << endl;

		myData += IP::ipHeaderLength;
		myLength -= IP::ipHeaderLength;
	
		myProtocol = header->protocol;
		mySourceIPAddress = header->sourceIPAddress;
		
		ICMPInPacket icmp(myData, myLength, this);
		icmp.decode();
	} else if (header->protocol == 0x06 /* TCP Packet */) {
		trace << "TCP Packet in!" << endl;
	
		myData += IP::ipHeaderLength;
		myLength -= IP::ipHeaderLength;
	
		myProtocol = header->protocol;
		mySourceIPAddress = header->sourceIPAddress;
	
		// For lab 4
		// TCPInPacket tcp(myData, myLength, this);
		// tcp.decode();
	}
}

void IPInPacket::answer(byte* theData, udword theLength)
{
	theData -= IP::ipHeaderLength;
	theLength += IP::ipHeaderLength;

	IPHeader * header = (IPHeader*) theData;
		
	header->versionNHeaderLength = 0x45; // Version = 4, header length = 20
	header->TypeOfService = 0x00;
	header->totalLength = HILO((uword)theLength);
	header->identification = 0x00; // No fragments yet
	header->fragmentFlagsNOffset = 0x40; // Don't fragment, Offset = 0 (Little endian)
	header->timeToLive = 0x40; // 64 hops
	header->protocol = myProtocol;
	header->headerChecksum = 0x00; // Must be 0 in order to calculate the checksum
	header->sourceIPAddress = IP::instance().myAddress();
	header->destinationIPAddress = mySourceIPAddress;
	
	// Calculate the checksum
	header->headerChecksum = calculateChecksum(theData, theLength, 0x00);
	
	myFrame->answer(theData, theLength);
}

uword IPInPacket::headerOffset()
{
	return myFrame->headerOffset() + IP::ipHeaderLength;
}
