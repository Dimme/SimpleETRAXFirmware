/*!***************************************************************************
*!
*! FILE NAME  : llc.cc
*!
*! DESCRIPTION: LLC dummy
*!
*!***************************************************************************/

/****************** INCLUDE FILES SECTION ***********************************/

#include "compiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "system.h"
}

#include "iostream.hh"
#include "ethernet.hh"
#include "llc.hh"
#include "arp.hh"
#include "ip.hh"

//#define D_LLC
#ifdef D_LLC
#define trace cout
#else
#define trace if(false) cout
#endif
/****************** LLC DEFINITION SECTION *************************/

//----------------------------------------------------------------------------
//
LLCInPacket::LLCInPacket(byte*           theData,
						 udword          theLength,
						 InPacket*       theFrame,
						 EthernetAddress theDestinationAddress,
						 EthernetAddress theSourceAddress,
						 uword           theTypeLen):
InPacket(theData, theLength, theFrame),
myDestinationAddress(theDestinationAddress),
mySourceAddress(theSourceAddress),
myTypeLen(theTypeLen)
{
}

//----------------------------------------------------------------------------
//
void LLCInPacket::decode()
{ 
	// Beware of the little endians in myTypeLen!
	if (myTypeLen == 0x0608) {
		trace << "ARP Packet in!" << endl;
	
		ARPInPacket arp(myData, myLength, this);
		arp.decode();
	} else if (myTypeLen == 0x0008 && myDestinationAddress == Ethernet::instance().myAddress()) {
		trace << "IP Packet in!" << endl;
	
		IPInPacket ip(myData, myLength, this);
		ip.decode();
	}
}

//----------------------------------------------------------------------------
//
void LLCInPacket::answer(byte *theData, udword theLength)
{
	myFrame->answer(theData, theLength);
}

uword LLCInPacket::headerOffset()
{
	return myFrame->headerOffset();
}

/****************** END OF FILE Ethernet.cc *************************************/

