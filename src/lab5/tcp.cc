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
#include "tcpsocket.hh"

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

// Is true when a connection is accepted on port portNo.
bool TCP::acceptConnection(uword portNo)
{
	return portNo == 7;
}

// Create a new TCPSocket. Register it in TCPConnection.
// Create and start a SimpleApplication. 
void TCP::connectionEstablished(TCPConnection* theConnection)
{
	if (theConnection->serverPortNumber() == 7) {
		// Create a new TCPSocket.
		TCPSocket* aSocket = new TCPSocket(theConnection);
		
		// Register the socket in the TCPConnection.
		theConnection->registerSocket(aSocket);
		
		// Create and start an application for the connection.
		Job::schedule(new SimpleApplication(aSocket));
	}
}


//----------------------------------------------------------------------------
//
RetransmissionTimer::RetransmissionTimer(TCPConnection * theConnection, Duration theTime) :
	myConnection(theConnection), myTime(theTime)
{	
}

void RetransmissionTimer::start()
{
	this->timeOutAfter(myTime);
}

void RetransmissionTimer::cancel()
{
	this->resetTimeOut();
}

void RetransmissionTimer::timeOut()
{
	myConnection->sendNext = myConnection->sentUnAcked;
	myConnection->myTCPSender->sendFromQueue();
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
	rTimer = new RetransmissionTimer(this, Clock::seconds);
}

// Return myPort.
uword TCPConnection::serverPortNumber()
{
	return myPort;
}
	
// Set mySocket to theSocket.
void  TCPConnection::registerSocket(TCPSocket* theSocket)
{
	mySocket = theSocket;
}


TCPConnection::~TCPConnection()
{
	trace << "TCP connection destroyed" << endl;
	delete myTCPSender;
	delete rTimer;
}

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
void TCPConnection::NetClose(uword withAck)
{
	myState->NetClose(this, withAck);
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
	if (theAcknowledgementNumber > sentUnAcked /** In case of strange problems: % 4294967296 **/) {
		// Setting the last acked segment
		sentUnAcked = theAcknowledgementNumber;
		
		// Checking if all sent data has been acked
		if (sentMaxSeq == sentUnAcked) {
			// Stop the retransmission timer
			rTimer->cancel();
		}
		
		myState->Acknowledge(this, theAcknowledgementNumber);
	}
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
void TCPState::NetClose(TCPConnection* theConnection, uword withAck) {}
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
	if (TCP::instance().acceptConnection(theConnection->myPort)) {
		theConnection->receiveNext = theSynchronizationNumber + 1;
		theConnection->receiveWindow = 8*1024;
		theConnection->sendNext = get_time();
		theConnection->sentMaxSeq = theConnection->sendNext;
		// Next reply to be sent
		theConnection->sentUnAcked = theConnection->sendNext;
		// Send a segment with the SYN and ACK flags set
		theConnection->myTCPSender->sendFlags(0x12);
		// Change state
		theConnection->myState = SynRecvdState::instance();
	} else {
		trace << "Not supported port! Sending RST..." << endl;
		theConnection->sendNext = 0;
		theConnection->sentMaxSeq = theConnection->sendNext;
		// Send a segment with the RST flag set
		theConnection->myTCPSender->sendFlags(0x04);
		TCP::instance().deleteConnection(theConnection);
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
	trace << "ACK received, changing to EstablishedState" << endl;
	
	// ACK is received and connection is now established
	// Tell that to TCP
	TCP::instance().connectionEstablished(theConnection);
		
	// Changing state to established
	theConnection->myState = EstablishedState::instance();
}


//----------------------------------------------------------------------------
//
EstablishedState* EstablishedState::instance()
{
	static EstablishedState myInstance;
	return &myInstance;
}

void EstablishedState::NetClose(TCPConnection* theConnection, uword withAck)
{
	trace << "EstablishedState::NetClose" << endl;

	// Update connection variables and send an ACK
	++(theConnection->receiveNext);
	theConnection->myTCPSender->sendFlags(0x10); // Sending an ACK
	
	// Go to NetClose wait state, inform application
	theConnection->myState = CloseWaitState::instance();

	// Tell to the socket that the connection has been closed
	// The application will call AppClose()
	theConnection->mySocket->socketEof();
}

//----------------------------------------------------------------------------
//
void EstablishedState::Receive(TCPConnection* theConnection, udword theSynchronizationNumber, byte* theData, udword theLength)
{
	trace << "EstablishedState::Receive" << endl;

	// Delayed ACK is not implemented, simply acknowledge the data
	// by sending an ACK segment, then echo the data using Send.
	
	if (theSynchronizationNumber == theConnection->receiveNext) {		
		theConnection->receiveNext += (theLength - TCP::tcpHeaderLength);
		theConnection->myTCPSender->sendFlags(0x10); // Sending an ACK
		
		theConnection->mySocket->socketDataReceived(theData + TCP::tcpHeaderLength, theLength - TCP::tcpHeaderLength);
	}
}

// Handle incoming Acknowledgement
void EstablishedState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	if (theConnection->theOffset >= theConnection->queueLength /** Last byte of the queue has been acked **/) {
		// TODO: Reset state variables
		theConnection->mySocket->socketDataSent();
	} else {
		theConnection->myTCPSender->sendFromQueue();
	}
}

// Send outgoing data
void EstablishedState::Send(TCPConnection* theConnection, byte* theData, udword theLength)
{
	theConnection->transmitQueue = theData;
	theConnection->queueLength = theLength;
	theConnection->firstSeq = theConnection->sendNext;
	theConnection->theOffset = 0;
	theConnection->theSendLength = 1460;
	
	theConnection->myTCPSender->sendFromQueue();
}

// Active close called from the application
void EstablishedState::AppClose(TCPConnection* theConnection)
{
	// Send a FIN
	theConnection->myTCPSender->sendFlags(0x01);
	
	// Switch to Fin Wait 1 state
	theConnection->myState = FinWait1State::instance();
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
	// Send a FIN
	theConnection->myTCPSender->sendFlags(0x11);
	
	// Switch to LastAck state
	theConnection->myState = LastAckState::instance();
}

// Handle incoming Acknowledgement
void CloseWaitState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	if (theConnection->theOffset >= theConnection->queueLength /** Last byte of the queue has been acked **/) {
		// TODO: Reset state variables
		theConnection->mySocket->socketDataSent();
	} else {
		theConnection->myTCPSender->sendFromQueue();
	}
}

// Send outgoing data
void CloseWaitState::Send(TCPConnection* theConnection, byte* theData, udword theLength)
{
	theConnection->transmitQueue = theData;
	theConnection->queueLength = theLength;
	theConnection->firstSeq = theConnection->sendNext;
	theConnection->theOffset = 0;
	theConnection->theSendLength = 1460;
	
	theConnection->myTCPSender->sendFromQueue();
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
	theConnection->Kill(); // Free the memory from the closed connection
}

FinWait1State* FinWait1State::instance()
{
	static FinWait1State myInstance;
	return &myInstance;
}

void FinWait1State::NetClose(TCPConnection* theConnection, uword withAck)
{
	// Send a ACK
	++(theConnection->receiveNext);
	theConnection->myTCPSender->sendFlags(0x10);
	
	// Jump to appropriate state
	if (withAck == 1) {
		theConnection->myState = TimeWaitState::instance(theConnection);
	}
	else
		theConnection->myState = ClosingState::instance();
}

void FinWait1State::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	// Jump to Fin Wait 2 State
	theConnection->myState = FinWait2State::instance();
}

FinWait2State* FinWait2State::instance()
{
	static FinWait2State myInstance;
	return &myInstance;
}

void FinWait2State::NetClose(TCPConnection* theConnection, uword withAck)
{
	// Send a ACK
	++(theConnection->receiveNext);
	theConnection->myTCPSender->sendFlags(0x10);
	
	// Jump to time wait state
	theConnection->myState = TimeWaitState::instance(theConnection);
}

ClosingState* ClosingState::instance()
{
	static ClosingState myInstance;
	return &myInstance;
}

void ClosingState::Acknowledge(TCPConnection* theConnection, udword theAcknowledgementNumber)
{
	// Jump to time wait state
	theConnection->myState = TimeWaitState::instance(theConnection);
}

TimeWaitState* TimeWaitState::instance(TCPConnection * theConnection)
{
	static TimeWaitState myInstance;
	
	TimeWaitStateTimer * timer = new TimeWaitStateTimer(Clock::seconds*2, theConnection);
	timer->start();
	
	return &myInstance;
}

TimeWaitStateTimer::TimeWaitStateTimer(Duration theWaitTime, TCPConnection * theConnection) : 
myWaitTime(theWaitTime), myConnection(theConnection)
{
}

void TimeWaitStateTimer::start()
{
	this->timeOutAfter(myWaitTime);
}

void TimeWaitStateTimer::timeOut()
{
	myConnection->Kill();
	delete this;
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
	
	if (theFlags != 0x10) { // If it is not an ACK
		++(myConnection->sendNext); // Increase the sequence number by one
		myConnection->sentMaxSeq = myConnection->sendNext;
	}
}

// Send a data segment. PSH and ACK flags are set.
void TCPSender::sendData(byte* theData, udword theLength)
{
	// Start the retransmission timer for each sent segment
	myConnection->rTimer->start();
	
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
	
	myConnection->sendNext += theLength;
	myConnection->sentMaxSeq = myConnection->sendNext;
}

// Send small chops of data
void TCPSender::sendFromQueue()
{
	udword theWindowSize = myConnection->myWindowSize - (myConnection->sendNext - myConnection->sentUnAcked);
	if (theWindowSize > myConnection->myWindowSize)
		theWindowSize = 0;
		
	udword dataToSend = myConnection->queueLength - myConnection->theOffset;
	
	// Check if we have to retransmitt a segment
	if (myConnection->sendNext < myConnection->sentMaxSeq) {
		udword leftLengthToMaxSeq = myConnection->sentMaxSeq - myConnection->sendNext;
		udword lengthToRetransmitt = leftLengthToMaxSeq < myConnection->theSendLength ?
				leftLengthToMaxSeq : myConnection->theSendLength;
	
		sendData(myConnection->transmitQueue + (myConnection->sendNext - myConnection->firstSeq), lengthToRetransmitt);
		myConnection->sendNext = myConnection->sentMaxSeq;
	}
	
	else if (dataToSend < myConnection->theSendLength) {
		sendData(myConnection->transmitQueue + myConnection->theOffset, dataToSend);
		myConnection->theOffset += dataToSend;
	} else {
		udword segmentsToSend = MIN(dataToSend, theWindowSize) / myConnection->theSendLength;
					
		for (udword i = 0; i < segmentsToSend; ++i) {
			sendData(myConnection->transmitQueue + myConnection->theOffset, myConnection->theSendLength);
			myConnection->theOffset += myConnection->theSendLength;
		}
	}
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
		// ACK Received
		if (aTCPHeader->flags == 0x10) {
			aConnection->Acknowledge(myAcknowledgementNumber);
		}
		
		// FIN Received
		else if (aTCPHeader->flags == 0x01) {
			aConnection->NetClose(0);
		}
		
		// FIN and ACK Received
		else if (aTCPHeader->flags == 0x11) {
			aConnection->NetClose(1);
		}
		
		// PSH and ACK Received
		else if (aTCPHeader->flags == 0x18) {
			aConnection->Receive(mySequenceNumber, myData, myLength);
		}
	}
	
	aConnection->myWindowSize = HILO(aTCPHeader->windowSize);
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
