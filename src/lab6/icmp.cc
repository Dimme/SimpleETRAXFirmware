#include "compiler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "system.h"
}

#include "iostream.hh"
#include "icmp.hh"

#define trace if(false) cout

ICMPInPacket::ICMPInPacket(byte* theData, udword theLength, InPacket* theFrame) : InPacket(theData, theLength, theFrame)
{
}

void ICMPInPacket::decode()
{
	ICMPHeader * header = (ICMPHeader*) myData;
	
	if (header->type == 0x08 && header->code == 0x00 /* ICMP ECHO Request */) {
		trace << "We have a ping ECHO request!" << endl;
		
		uword hoffs = myFrame->headerOffset();

		byte* temp = new byte[myLength + hoffs];
		byte* replyData = temp + hoffs;
		
		this->answer(replyData, myLength);
	}
}

void ICMPInPacket::answer(byte* theData, udword theLength)
{
	ICMPHeader * header = (ICMPHeader*) theData;
	
	header->type = 0x00;
	header->code = 0x00;
	header->checksum = ((ICMPHeader*) myData)->checksum + 0x08;
	
	memcpy(theData + icmpHeaderLen, myData + icmpHeaderLen, myLength - icmpHeaderLen);
	
	myFrame->answer(theData, theLength);
}

uword ICMPInPacket::headerOffset()
{
	return myFrame->headerOffset() + icmpHeaderLen;
}
