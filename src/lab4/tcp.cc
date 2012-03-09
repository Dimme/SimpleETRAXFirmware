/*!***************************************************************************
*!
*! FILE NAME  : tcp.cc
*!
*! DESCRIPTION: TCP, Transport control protocol
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
#include "timr.h"
}

#include "iostream.hh"
#include "tcp.hh"
#include "ip.hh"

//#define D_TCP
#ifdef D_TCP
#define trace cout
#else
#define trace if(false) cout
#endif
/****************** TCP DEFINITION SECTION *************************/

//----------------------------------------------------------------------------
//
TCP::TCP()
{
	trace << "TCP created." << endl;
}

//----------------------------------------------------------------------------
//
TCP& TCP::instance()
{
	static TCP myInstance;
	return myInstance;
}

//----------------------------------------------------------------------------
//
TCPConnection* TCP::getConnection(IPAddress& theSourceAddress, uword theSourcePort, uword theDestinationPort)
{
	TCPConnection* aConnection = NULL;
	// Find among open connections
	uword queueLength = myConnectionList.Length();
	myConnectionList.ResetIterator();
	bool connectionFound = false;
	while ((queueLength-- > 0) && !connectionFound)
	{
		aConnection = myConnectionList.Next();
		connectionFound = aConnection->tryConnection(theSourceAddress,
			theSourcePort,
			theDestinationPort);
	}
	if (!connectionFound)
	{
		trace << "Connection not found!" << endl;
		aConnection = NULL;
	}
	else
	{
		trace << "Found connection in queue" << endl;
	}
	return aConnection;
}

//----------------------------------------------------------------------------
//
TCPConnection* TCP::createConnection(IPAddress& theSourceAddress,
									 uword      theSourcePort,
									 uword      theDestinationPort,
									 InPacket*  theCreator)
{
	TCPConnection* aConnection =  new TCPConnection(theSourceAddress,
		theSourcePort,
		theDestinationPort,
		theCreator);
	myConnectionList.Append(aConnection);
	return aConnection;
}

//----------------------------------------------------------------------------
//
void TCP::deleteConnection(TCPConnection* theConnection)
{
	myConnectionList.Remove(theConnection);
	delete theConnection;
}

//----------------------------------------------------------------------------
//
TCPConnection::TCPConnection(IPAddress& theSourceAddress,
							 uword      theSourcePort,
							 uword      theDestinationPort,
							 InPacket*  theCreator):
hisAddress(theSourceAddress),
hisPort(theSourcePort),
myPort(theDestinationPort)
{
	trace << "TCP connection created" << endl;
	myTCPSender = new TCPSender(this, theCreator);
	myState = ListenState::instance();
}

//----------------------------------------------------------------------------
//
TCPConnection::~TCPConnection()
{
	trace << "TCP connection destroyed" << endl;
	delete myTCPSender;
}

//----------------------------------------------------------------------------
//
bool TCPConnection::tryConnection(IPAddress& theSourceAddress, 
								  uword theSourcePort, 
								  uword theDestinationPort)
{
	return (theSourcePort   == hisPort   ) &&
		(theDestinationPort == myPort    ) &&
		(theSourceAddress   == hisAddress);
}

// Handle an incoming SYN segment
void TCPConnection::Synchronize(udword theSynchronizationNumber)
{	
	myState->Synchronize(this, theSynchronizationNumber);
}

// Handle an incoming FIN segment
void TCPConnection::NetClose()
{
	myState->NetClose(this);
}

// Handle close from application
void TCPConnection::AppClose()
{
	myState->AppClose(this);
}

// Handle an incoming RST segment, can also called in other error conditions
void TCPConnection::Kill()
{
	myState->Kill(this);
}

// Handle incoming data
void TCPConnection::Receive(udword theSynchronizationNumber, byte*  theData, udword theLength)
{
	myState->Receive(this, theSynchronizationNumber, theData, theLength);
}

// Handle incoming Acknowledgement
void TCPConnection::Acknowledge(udword theAcknowledgementNumber)
{
	myState->Acknowledge(this, theAcknowledgementNumber);
}

// Send data
void TCPConnection::Send(byte* theData, udword theLength)
{
	myState->Send(this, theData, theLength);
}


//----------------------------------------------------------------------------
// TCPState contains dummies for all the operations, only the interesting ones
// gets overloaded by the various sub classes.


//----------------------------------------------------------------------------
//
// Handle an incoming RST segment, can also called in other error conditions
void TCPState::Kill(TCPConnection* theConnection)
{
	trace << "TCPState::Kill" << endl;
	TCP::instance().deleteConnection(theConnection);
}

// Stub TCPState methods
void TCPState::Synchronize(TCPConnection* theConnection, udword theSynchronizationNumber) {}
void TCPState::NetClose(TCPConnection* theConnection) {}
void TCPState::AppClose(TCPConnection* theConnection) {}
void TCPState::Receive(TCPConnection* theConnection, udword theSynchronizationNumber, byte*  theData, udword theLength) {}
void TCPState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber) {}
void TCPState::Send(TCPConnection* theConnection, byte*  theData, udword theLength) {}

//----------------------------------------------------------------------------
//
ListenState* ListenState::instance()
{
	static ListenState myInstance;
	return &myInstance;
}

// Handle an incoming SYN segment
void ListenState::Synchronize(TCPConnection* theConnection, udword theSynchronizationNumber)
{
	switch (theConnection->myPort) {
	case 7:
		trace << "Got SYN on ECHO port" << endl;
		theConnection->receiveNext = theSynchronizationNumber + 1;
		theConnection->receiveWindow = 8*1024;
		theConnection->sendNext = get_time();
		// Next reply to be sent
		theConnection->sentUnAcked = theConnection->sendNext;
		// Send a segment with the SYN and ACK flags set
		theConnection->myTCPSender->sendFlags(0x12);
		// Prepare for the next send operation
		++(theConnection->sendNext);
		// Change state
		theConnection->myState = SynRecvdState::instance();
		break;
	default:
		trace << "Not supported port! Sending RST..." << endl;
		theConnection->sendNext = 0;
		// Send a segment with the RST flag set
		theConnection->myTCPSender->sendFlags(0x04);
		TCP::instance().deleteConnection(theConnection);
		break;
	}
}

//----------------------------------------------------------------------------
//
SynRecvdState* SynRecvdState::instance()
{
	static SynRecvdState myInstance;
	return &myInstance;
}

// Handle incoming Acknowledgement
void SynRecvdState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	if (theAcknowledgementNumber > theConnection->sentUnAcked) {
		trace << "ACK received, changing to EstablishedState" << endl;
		// Setting the last acked segment
		theConnection->sentUnAcked = theAcknowledgementNumber;
		
		// Changing state to established
		theConnection->myState = EstablishedState::instance();
	}
}


//----------------------------------------------------------------------------
//
EstablishedState* EstablishedState::instance()
{
	static EstablishedState myInstance;
	return &myInstance;
}

void EstablishedState::NetClose(TCPConnection* theConnection)
{
	trace << "EstablishedState::NetClose" << endl;

	// Update connection variables and send an ACK
	++(theConnection->receiveNext);
	theConnection->myTCPSender->sendFlags(0x10); // Sending an ACK

	// Go to NetClose wait state, inform application
	theConnection->myState = CloseWaitState::instance();

	// Normally the application would be notified next and nothing
	// happen until the application calls appClose on the connection.
	// Since we don't have an application we simply call appClose here instead.

	// Simulate application Close...
	theConnection->AppClose();
	
	theConnection->Kill(); // Free the memory from the closed connection
}

//----------------------------------------------------------------------------
//
void EstablishedState::Receive(TCPConnection* theConnection, udword theSynchronizationNumber, byte* theData, udword theLength)
{
	trace << "EstablishedState::Receive" << endl;

	// Delayed ACK is not implemented, simply acknowledge the data
	// by sending an ACK segment, then echo the data using Send.
	
	if (theSynchronizationNumber == theConnection->receiveNext) {
		// How to remove Ethernet trailer from theLength ???
		
		theConnection->receiveNext += (theLength - TCP::tcpHeaderLength);
		theConnection->myTCPSender->sendFlags(0x10); // Sending an ACK
		
		Send(theConnection, theData + TCP::tcpHeaderLength, theLength - TCP::tcpHeaderLength);
	}
}

// Handle incoming Acknowledgement
void EstablishedState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	if (theAcknowledgementNumber > theConnection->sentUnAcked) {
		// Setting the last acked segment
		theConnection->sentUnAcked = theAcknowledgementNumber;
	}
}

// Send outgoing data
void EstablishedState::Send(TCPConnection* theConnection, byte*  theData, udword theLength)
{
	theConnection->myTCPSender->sendData(theData, theLength);
	theConnection->sendNext += theLength;
}


//----------------------------------------------------------------------------
//
CloseWaitState* CloseWaitState::instance()
{
	static CloseWaitState myInstance;
	return &myInstance;
}

// Handle close from application
void CloseWaitState::AppClose(TCPConnection* theConnection)
{
	// TODO: Implement this!
}

//----------------------------------------------------------------------------
//
LastAckState* LastAckState::instance()
{
	static LastAckState myInstance;
	return &myInstance;
}

// Handle incoming Acknowledgement
void LastAckState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	// TODO: Implement this!
}

//----------------------------------------------------------------------------
//
TCPSender::TCPSender(TCPConnection* theConnection, 
					 InPacket*      theCreator):
myConnection(theConnection),
myAnswerChain(theCreator->copyAnswerChain()) // Copies InPacket chain!
{
}

TCPSender::~TCPSender()
{
	myAnswerChain->deleteAnswerChain();
}

// Send a flag segment without data.
void TCPSender::sendFlags(byte theFlags)
{
	uword hoffs = myAnswerChain->headerOffset(); // myAnswerChain refers to the IPInPacket / the layer bellow
	uword totalSegmentLength = TCP::tcpHeaderLength; // Data = 0 as we are sending only flags
	
	byte * temp = new byte[hoffs + totalSegmentLength];
	byte * anAnswer = temp + hoffs;
	
	TCPHeader * aTCPHeader = (TCPHeader *) anAnswer;
	
	aTCPHeader->sourcePort = HILO(myConnection->myPort);
	aTCPHeader->destinationPort = HILO(myConnection->hisPort);
	aTCPHeader->sequenceNumber = LHILO(myConnection->sendNext);
	aTCPHeader->acknowledgementNumber = LHILO(myConnection->receiveNext);
	aTCPHeader->headerLength = (byte) (TCP::tcpHeaderLength << 2);
	aTCPHeader->flags = theFlags;
	aTCPHeader->windowSize = HILO(myConnection->receiveWindow);
	aTCPHeader->checksum = 0x00;

	// Calculate the pseudo header checksum
	TCPPseudoHeader aPseudoHeader(myConnection->hisAddress, totalSegmentLength);
	uword pseudosum = aPseudoHeader.checksum();
	
	aTCPHeader->checksum = calculateChecksum(anAnswer, totalSegmentLength, pseudosum);
	
	// Send the TCP segment
	myAnswerChain->answer(anAnswer, totalSegmentLength);
}

// Send a data segment. PSH and ACK flags are set.
void TCPSender::sendData(byte* theData, udword theLength)
{
	uword hoffs = myAnswerChain->headerOffset(); // myAnswerChain refers to the IPInPacket / the layer bellow
	udword totalSegmentLength = TCP::tcpHeaderLength + theLength;
	
	byte * temp = new byte[hoffs + totalSegmentLength];
	byte * anAnswer = temp + hoffs;
	
	TCPHeader * aTCPHeader = (TCPHeader *) anAnswer;
	
	aTCPHeader->sourcePort = HILO(myConnection->myPort);
	aTCPHeader->destinationPort = HILO(myConnection->hisPort);
	aTCPHeader->sequenceNumber = LHILO(myConnection->sendNext);
	aTCPHeader->acknowledgementNumber = LHILO(myConnection->receiveNext);
	aTCPHeader->headerLength = (byte) (TCP::tcpHeaderLength << 2);
	aTCPHeader->flags = 0x18; // PSH and ACK
	aTCPHeader->windowSize = HILO(myConnection->receiveWindow);
	aTCPHeader->checksum = 0x00;
	
	memcpy(anAnswer+TCP::tcpHeaderLength, theData, theLength);

	// Calculate the pseudo header checksum
	TCPPseudoHeader aPseudoHeader(myConnection->hisAddress, totalSegmentLength);
	uword pseudosum = aPseudoHeader.checksum();
	
	aTCPHeader->checksum = calculateChecksum(anAnswer, totalSegmentLength, pseudosum);
	
	// Send the TCP segment
	myAnswerChain->answer(anAnswer, totalSegmentLength);
}


//----------------------------------------------------------------------------
//
TCPInPacket::TCPInPacket(byte* theData,
						 udword theLength,
						 InPacket* theFrame,
						 IPAddress& theSourceAddress):	
InPacket(theData, theLength, theFrame),
mySourceAddress(theSourceAddress)
{	
}

void TCPInPacket::decode()
{	
	// Get the TCP header
	TCPHeader * aTCPHeader = (TCPHeader *) myData;
	
	// Retrieve packet information from the header
	mySourcePort = HILO(aTCPHeader->sourcePort);
	myDestinationPort = HILO(aTCPHeader->destinationPort);
	mySequenceNumber = LHILO(aTCPHeader->sequenceNumber);
	myAcknowledgementNumber = LHILO(aTCPHeader->acknowledgementNumber);
	
	trace << "Incoming TCP! Source port: " << mySourcePort << " Destination port: " << myDestinationPort << " Seq: " << mySequenceNumber << " Ack: " << myAcknowledgementNumber << endl;
	
	// Assuming that this TCP connection already exists, try to get it
	TCPConnection * aConnection = TCP::instance().getConnection(mySourceAddress, mySourcePort, myDestinationPort);
	
	if (!aConnection) {
		// If it doesn't exist, create it
		aConnection = TCP::instance().createConnection(mySourceAddress, mySourcePort, myDestinationPort, this);
		
		if ((aTCPHeader->flags & 0x02) != 0) {
			// State LISTEN. Received a SYN flag.
			aConnection->Synchronize(mySequenceNumber);
		} else {
			// State LISTEN. No SYN flag. Impossible to continue.
			aConnection->Kill();
		}
		
	} else {
		// TODO: Connection was established. Handle all states.
		
		// ACK Received
		if (aTCPHeader->flags == 0x10) {
			aConnection->Acknowledge(myAcknowledgementNumber);
		}
		
		// FIN and ACK Received
		else if (aTCPHeader->flags == 0x11) {
			aConnection->NetClose();
		}
		
		// PSH and ACK Received
		else if (aTCPHeader->flags == 0x18) {
			aConnection->Receive(mySequenceNumber, myData, myLength);
		}
	}
}

void TCPInPacket::answer(byte* theData, udword theLength)
{
	// TODO: Implement this!
}

uword TCPInPacket::headerOffset()
{
	return myFrame->headerOffset() + TCP::tcpHeaderLength; // Change this
}

InPacket* TCPInPacket::copyAnswerChain()
{  
	return myFrame->copyAnswerChain();
}



//----------------------------------------------------------------------------
//
TCPPseudoHeader::TCPPseudoHeader(IPAddress& theDestination,
								 uword theLength):
sourceIPAddress(IP::instance().myAddress()),
destinationIPAddress(theDestination),
zero(0),
protocol(6)
{
	tcpLength = HILO(theLength);
}

uword TCPPseudoHeader::checksum()
{
	return calculateChecksum((byte*)this, 12);
}


/****************** END OF FILE tcp.cc *************************************/

