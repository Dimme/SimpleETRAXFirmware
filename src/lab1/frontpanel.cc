/*!***************************************************************************
*!
*! FILE NAME  : FrontPanel.cc
*!
*! DESCRIPTION: Handles the LED:s
*!
*!***************************************************************************/

/****************** INCLUDE FILES SECTION ***********************************/

#include "compiler.h"

#include "iostream.hh"
#include "frontpanel.hh"

//#define D_FP
#ifdef D_FP
#define trace cout
#else
#define trace if(false) cout
#endif

/* LED */

// Create an LED instance
LED::LED(byte theLedNumber) : myLedBit(theLedNumber)
{
}

// Some kind of magic register
static byte write_out_register_shadow = 0x78;

// Turn on an LED
void LED::on()
{
	uword led = 4 << myLedBit;  /* convert LED number to bit weight */
	*(VOLATILE byte*)0x80000000 = write_out_register_shadow &= ~led;
	iAmOn = 1;
}

// Turn off an LED
void LED::off()
{
	uword led = 4 << myLedBit;  /* convert LED number to bit weight */
	*(VOLATILE byte*)0x80000000 = write_out_register_shadow |= led;
	iAmOn = 0;
}

// Toggle the state on an LED
void LED::toggle()
{
	if (iAmOn)
		off();
	else
		on();
}

/* Network LED Timer */

// Create the Network LED timer
NetworkLEDTimer::NetworkLEDTimer(Duration blinkTime) : myBlinkTime(blinkTime)
{
}

// Start the Network LED timer
void NetworkLEDTimer::start()
{
	this->timeOutAfter(myBlinkTime); 
}
 
// Notify the front panel when the timer times-out
void NetworkLEDTimer::timeOut()
{
	FrontPanel::instance().notifyLedEvent(FrontPanel::instance().networkLedId);
}

/* CD LED Timer */

// Create and start the CD LED timer
CDLEDTimer::CDLEDTimer(Duration blinkPeriod) : PeriodicTimed()
{
	timerInterval(blinkPeriod);
	startPeriodicTimer();
}

// Notify the front panel when the timer times-out for a period
void CDLEDTimer::timerNotify()
{
	FrontPanel::instance().notifyLedEvent(FrontPanel::instance().cdLedId);
}

/* Status LED Timer */

// Create and start the Status LED timer
StatusLEDTimer::StatusLEDTimer(Duration blinkPeriod) : PeriodicTimed()
{
	timerInterval(blinkPeriod);
	startPeriodicTimer();
}

// Notify the front panel when the timer times-out for a period
void StatusLEDTimer::timerNotify()
{
	FrontPanel::instance().notifyLedEvent(FrontPanel::instance().statusLedId);
}

/* Front panel */

// Create and return the singleton instance of the front panel
FrontPanel& FrontPanel::instance()
{
	static FrontPanel instance;
	return instance;
}

// Blink once when a packet is received, called by some other class
void FrontPanel::packetReceived()
{	
	myNetworkLEDTimer = new NetworkLEDTimer(Clock::tics*10);
	myNetworkLED.on();
	myNetworkLEDTimer->start();
}

// Called by the timers when the time-out
void FrontPanel::notifyLedEvent(uword theLedId)
{
	switch (theLedId) {
	case networkLedId:
		myNetworkLED.off();
		delete myNetworkLEDTimer;
		break;
		
	case cdLedId:
		myCDLED.toggle();
		break;
		
	case statusLedId:
		myStatusLED.toggle();
		break;
	}
}

// Create a front panel and set the static LED instances
FrontPanel::FrontPanel() : mySemaphore(Semaphore::createQueueSemaphore("led",0)),
								myNetworkLED(LED::LED(networkLedId)), 
								myCDLED(LED::LED(cdLedId)), 
								myStatusLED(LED::LED(statusLedId))
{
	// Demonstrate the network blinking LED by blinking once
	packetReceived();

	// Illuminate the blinking CD LED
	myCDLEDTimer = new CDLEDTimer(Clock::tics*60);
	
	// Illuminate the blinking Status LED
	myStatusLEDTimer = new StatusLEDTimer(Clock::tics*4);
}

void FrontPanel::doit()
{
}

