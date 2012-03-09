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
#include "tcpsocket.hh"
#include "tcp.hh"
#include "threads.hh"

//#define D_TCPSOCK
#ifdef D_TCPSOCK
#define trace cout
#else
#define trace if(false) cout
#endif

// Constructor. The socket is created by class TCP when a connection is
// established. create the semaphores
TCPSocket::TCPSocket(TCPConnection* theConnection) : 
						myConnection(theConnection),
						myReadSemaphore(Semaphore::createQueueSemaphore("Read",0)),
						myWriteSemaphore(Semaphore::createQueueSemaphore("Write",0)),
						eofFound(false)
{
}
  
// Destructor. Seek and Destroy the semaphores.
//
// Interface to application
//  
TCPSocket::~TCPSocket()
{
	delete myReadSemaphore;
	delete myWriteSemaphore;
	
	// TODO: Interface to application
}
  
// Read incoming data segment. This call will block on the read semaphore
// until data is available.
// theLength returns the amount of data read.
byte* TCPSocket::Read(udword& theLength)
{
	myReadSemaphore->wait(); // Wait for available data
	theLength = myReadLength;
	byte* aData = myReadData;
	myReadLength = 0;
	myReadData = 0;
	
	return aData; 
}
  
// True if a FIN has been received from the remote host.
bool TCPSocket::isEof()
{
	return eofFound;
}
  
// Write data to remote host. This call will block on the write semaphore
// until all the data has been sent to, and acknowledged by, the remote host.
void TCPSocket::Write(byte* theData, udword theLength)
{
	myConnection->Send(theData, theLength);
	myWriteSemaphore->wait(); // Wait until the data is acknowledged 
}

// Close the socket. When called the socket will close the connection by
// calling myConnection->AppClose() and delete itself.
//
// Interface to TCPConnection
//
void TCPSocket::Close()
{
	myConnection->AppClose();
	delete this;
}
  
// Called from TCP when data has been received. signals the read semaphore.
void TCPSocket::socketDataReceived(byte* theData, udword theLength)
{
	myReadData = new byte[theLength];
	memcpy(myReadData, theData, theLength);
	myReadLength = theLength;
	myReadSemaphore->signal(); // Data is available 
}

// Called from TCP when all data has been sent and acknowledged. signals
// the write semaphore.
void TCPSocket::socketDataSent()
{
	myWriteSemaphore->signal(); // The data has been acknowledged 
}

// Called from TCP when a FIN has been received in the established state.
// Sets the eofFound flag and signals the read semaphore.
void TCPSocket::socketEof()
{
	eofFound = true;
	myReadSemaphore->signal();
}

// Constructor. The application is created by class TCP when a connection is
// established.
SimpleApplication::SimpleApplication(TCPSocket* theSocket) : mySocket(theSocket)
{
}
  
// Gets called when the application thread begins execution.
// The SimpleApplication job is scheduled by TCP when a connection is
// established.
void SimpleApplication::doit()
{
	udword aLength;
	byte* aData;
	bool done = false;
	while (!done && !mySocket->isEof()) {
	
		aData = mySocket->Read(aLength);
		
		if (aLength > 0) {
			if ((char)*aData == 'q') {
				done = true;
				mySocket->Write((byte*)"Bye bye!\n", 10);
			} else if ((char)*aData == 's') {
				byte * data = new byte[10240];
				for (uword i = 0; i < 10240; ++i) {
					data[i] = (byte) 'A';
				}
				mySocket->Write(data, 10240);
				delete [] data;
			} else if ((char)*aData == 'f') {
				byte * data = new byte[1048576];
				for (word i = 0; i < 10; ++i) {
					mySocket->Write(data, 1048576);
				}
				delete [] data;
			} else
				mySocket->Write(aData, aLength);
			
			delete [] aData;
		}
	}
	mySocket->Close(); 
}
