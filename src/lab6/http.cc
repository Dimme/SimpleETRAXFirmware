/*!***************************************************************************
*!
*! FILE NAME  : http.cc
*!
*! DESCRIPTION: HTTP, Hyper text transfer protocol.
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
#include "tcpsocket.hh"
#include "http.hh"
#include "fs.hh"

//#define D_HTTP
#ifdef D_HTTP
#define trace cout
#else
#define trace if(false) cout
#endif

/****************** HTTPServer DEFINITION SECTION ***************************/


// Constructor. The application is created by class TCP when a connection is
// established.
HTTPServer::HTTPServer(TCPSocket* theSocket) : mySocket(theSocket)
{
}
  
// Gets called when the application thread begins execution.
// The HTTPServer job is scheduled by TCP when a connection is
// established.
void HTTPServer::doit()
{
	char * requestString = new char[5000];
	//*requestString = '\0'; // Empty string
	
	udword countHeaderData = 0;
	while (!mySocket->isEof()) {
		// Read a string from the socket and save it in the buffer
		udword aLength;
		byte * aData = mySocket->Read(aLength);
		
		memcpy(requestString + countHeaderData, aData, aLength);
		countHeaderData += aLength;
		*(requestString + countHeaderData) = '\0';
		delete [] aData;
		
		// Check if the whole header has been read into the buffer
		char * headerEnd = strstr(requestString, "\r\n\r\n");
		if (headerEnd) {
		
			// Referense to the header
			*headerEnd = '\0';
			char * header = requestString;
		
			// Extract the contentLength of the header
			udword contLength = contentLength(header, headerEnd-header);
			
			// If the contentLength is more than 0 we have a header and a body in the request
			char * body = 0;
			if (contLength > 0) {
							
				// Read the rest of the content from the socket
				udword countLength = countHeaderData-(headerEnd-header)-4;
				while (countLength < contLength) {
					udword bLength;
					byte * bData = mySocket->Read(bLength);
					memcpy(headerEnd+4 + countLength, bData, bLength);
					countLength += bLength;
					delete [] bData;
				}
							
				// Referense to the body
				body = (char *)(headerEnd + 4);
				*(body+countLength) = '\0';
				cout << "Request length: " << (udword)((body+countLength)-requestString) << endl;
			}
			
			// Find out the method used by the web browser
			if (!strncmp(header, "GET", 3)) {
				// GET
				getReq(header);
			} else if (!strncmp(header, "POST", 4)) {
				// POST with body
				postReq(header, body);
			} else {
				// HEAD
				udword devnull;
				headReq(header, devnull, false);
			}
						
			// The whole TCP request has been read and processed
			// Break out of the loop
			break;
		}
	}
	
	delete [] requestString;
	
	// Done, close the connection
	mySocket->Close();
}

byte* HTTPServer::headReq(char* theHeader, udword &contLength, bool withBody)
{
	// Find out the path
	*(strstr(theHeader, "\r\n")) = '\0';
	char * path = findPathName(theHeader);
	
	// Find out the file name
	*(strrchr(theHeader, ' ')) = '\0';
	char * filename = (char *)(strrchr(theHeader, '/') + 1);
	
	// Check if it is index
	if (*filename == '\0')
		filename = "index.htm";
	
	// Check if file exists
	byte * content = FileSystem::instance().readFile(path, filename, contLength);
	if (!content) {
		// Send 404 Not found error and return
		sendError(404, withBody);
		return 0;
	}
	
	// Check if the filename is password protected
	if (!strcmp(filename, "private.htm")) {
	
		// Try to find the supplied password
		char * headerRest = (char *)(theHeader + strlen(theHeader) + 1);
		headerRest += (strlen(headerRest) + 2);
		char * password = strstr(headerRest, "Authorization: Basic ");
		
		// If not password was given
		if (!password) {
			
			// Send 401 Unauthorized error and return
			sendError(401, withBody);
			return 0;
		}
		
		// Pick out the password
		password += 21;
		*(strstr(password, "\r\n")) = '\0';
		
		// If password is not "monkey"
		char * decodedPassword = decodeBase64(password);
		
		if (strcmp(decodedPassword, "monkey:monkey")) {
		
			// Send 401 Unauthorized error and return
			sendError(401, withBody);
			return 0;
		}
		delete [] decodedPassword;
	}
	
	// Find out the extension
	char * ext = (char *)(strchr(theHeader, '.') + 1);
	
	// Prepare the header for the requested extension
	char * header;
	if (!strcmp(ext, "gif")) {
		header = 	"HTTP/1.0 200 OK\r\n"
					"Content-Type: image/gif\r\n"
					"Content-Length: ";
	} else if (!strcmp(ext, "jpg")) {
		header = 	"HTTP/1.0 200 OK\r\n"
					"Content-Type: image/jpeg\r\n"
					"Content-Length: ";
	} else {
		header = 	"HTTP/1.0 200 OK\r\n"
					"Content-Type: text/html\r\n"
					"Content-Length: ";
	}
	
	char contentLengthString[10];
	*contentLengthString = '\0';
	sprintf(contentLengthString,"%d",contLength);
		
	mySocket->Write((byte*) header, 			strlen(header));
	mySocket->Write((byte*) contentLengthString,strlen(contentLengthString));
	mySocket->Write((byte*) "\r\n\r\n", 		4);
	
	delete [] path;
	
	return content;
}

void HTTPServer::getReq(char* theHeader)
{
	// Simulate a HEAD request
	udword contLength;
	byte * content = headReq(theHeader, contLength, true);
	
	// and send the content it returns
	if (content)
		mySocket->Write(content, contLength);
}

void HTTPServer::postReq(char* theHeader, char* theBody)
{	
	// Decode the body
	char * body = decodeForm(theBody);
	
	// Write the file to memory
	FileSystem::instance().writeFile((byte*) body, strlen(body)+1);
	
	// Simulate a GET request
	getReq(theHeader);
	
	delete [] body;
}

void HTTPServer::sendError(uword theError, bool withBody)
{
	char * error;
	switch (theError) {
	case 404:
		error = 	(char*)
					(withBody ?
					"HTTP/1.0 404 Not found\r\n"
					"Content-Type: text/html\r\n"
					"\r\n"
					"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
					"<html><head>"
					"<title>404 Not Found</title>"
					"</head><body>"
					"<h1>Not Found</h1>"
					"<p>The requested URL was stolen by a monkey.</p>"
					"<hr>"
					"<address>ETRAXhttpd/0.0.1 (ETRAX OS) Server</address>"
					"</body></html>"
					:
					"HTTP/1.0 404 Not found\r\n"
					"Content-Type: text/html\r\n"
					"\r\n");
		break;
	case 401:
		error = 	(char*)
					(withBody ?
					"HTTP/1.0 401 Unauthorized\r\n"
					"Content-Type: text/html\r\n"
					"WWW-Authenticate: Basic realm=\"Private Monkey Business\"\r\n"
					"\r\n"
					"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
					"<html><head>"
					"<title>401 Unauthorized</title>"
					"</head><body>"
					"<h1>Unauthorized</h1>"
					"<p>This monkey wants a password.</p>"
					"<hr>"
					"<address>ETRAXhttpd/0.0.1 (ETRAX OS) Server</address>"
					"</body></html>"
					:
					"HTTP/1.0 401 Unauthorized\r\n"
					"Content-Type: text/html\r\n"
					"WWW-Authenticate: Basic realm=\"Private Monkey Business\"\r\n"
					"\r\n");
		break;
	default:
		error = 	(char*)
					(withBody ?
					"HTTP/1.0 500 Internal server error\r\n"
					"Content-Type: text/html\r\n"
					"\r\n"
					"<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML 2.0//EN\">"
					"<html><head>"
					"<title>500 Internal server error</title>"
					"</head><body>"
					"<h1>Internal server error</h1>"
					"<p>The monkey that coded this program was tired.</p>"
					"<hr>"
					"<address>ETRAXhttpd/0.0.1 (ETRAX OS) Server</address>"
					"</body></html>"
					:
					"HTTP/1.0 500 Internal server error\r\n"
					"Content-Type: text/html\r\n"
					"\r\n");
		break;
	}

	mySocket->Write((byte *) error, strlen(error));
}

//----------------------------------------------------------------------------
//
// Allocates a new null terminated string containing a copy of the data at
// 'thePosition', 'theLength' characters long. The string must be deleted by
// the caller.
//
char* HTTPServer::extractString(char* thePosition, udword theLength)
{
	char* aString = new char[theLength + 1];
	strncpy(aString, thePosition, theLength);
	aString[theLength] = '\0';
	return aString;
}

//----------------------------------------------------------------------------
//
// Will look for the 'Content-Length' field in the request header and convert
// the length to a udword
// theData is a pointer to the request. theLength is the total length of the
// request.
//
udword HTTPServer::contentLength(char* theData, udword theLength)
{
	udword index = 0;
	bool   lenFound = false;
	const char* aSearchString = "Content-Length: ";
	while ((index++ < theLength) && !lenFound)
	{
		lenFound = (strncmp(theData + index,
			aSearchString,
			strlen(aSearchString)) == 0);
	}
	if (!lenFound)
	{
		return 0;
	}
	trace << "Found Content-Length!" << endl;
	index += strlen(aSearchString) - 1;
	char* lenStart = theData + index;
	char* lenEnd = strchr(theData + index, '\0');
	char* lenString = this->extractString(lenStart, lenEnd - lenStart);
	udword contLen = atoi(lenString);
	trace << "lenString: " << lenString << " is len: " << contLen << endl;
	delete [] lenString;
	return contLen;
}

//----------------------------------------------------------------------------
//
// Decode user and password for basic authentication.
// returns a decoded string that must be deleted by the caller.
//
char* HTTPServer::decodeBase64(char* theEncodedString)
{
	static const char* someValidCharacters =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

	int aCharsToDecode;
	int k = 0;
	char  aTmpStorage[4];
	int aValue;
	char* aResult = new char[80];

	// Original code by JH, found on the net years later (!).
	// Modify on your own risk. 

	for (unsigned int i = 0; i < strlen(theEncodedString); i += 4)
	{
		aValue = 0;
		aCharsToDecode = 3;
		if (theEncodedString[i+2] == '=')
		{
			aCharsToDecode = 1;
		}
		else if (theEncodedString[i+3] == '=')
		{
			aCharsToDecode = 2;
		}

		for (int j = 0; j <= aCharsToDecode; j++)
		{
			int aDecodedValue;
			aDecodedValue = strchr(someValidCharacters,theEncodedString[i+j])
				- someValidCharacters;
			aDecodedValue <<= ((3-j)*6);
			aValue += aDecodedValue;
		}
		for (int jj = 2; jj >= 0; jj--) 
		{
			aTmpStorage[jj] = aValue & 255;
			aValue >>= 8;
		}
		aResult[k++] = aTmpStorage[0];
		aResult[k++] = aTmpStorage[1];
		aResult[k++] = aTmpStorage[2];
	}
	aResult[k] = 0; // zero terminate string

	return aResult;  
}

//------------------------------------------------------------------------
//
// Decode the URL encoded data submitted in a POST.
//
char* HTTPServer::decodeForm(char* theEncodedForm)
{
	char* anEncodedFile = strchr(theEncodedForm,'=');
	anEncodedFile++;
	char* aForm = new char[strlen(anEncodedFile) * 2]; 
	// Serious overkill, but what the heck, we've got plenty of memory here!
	udword aSourceIndex = 0;
	udword aDestIndex = 0;

	while (aSourceIndex < strlen(anEncodedFile))
	{
		char aChar = *(anEncodedFile + aSourceIndex++);
		switch (aChar)
		{
		case '&':
			*(aForm + aDestIndex++) = '\r';
			*(aForm + aDestIndex++) = '\n';
			break;
		case '+':
			*(aForm + aDestIndex++) = ' ';
			break;
		case '%':
			char aTemp[5];
			aTemp[0] = '0';
			aTemp[1] = 'x';
			aTemp[2] = *(anEncodedFile + aSourceIndex++);
			aTemp[3] = *(anEncodedFile + aSourceIndex++);
			aTemp[4] = '\0';
			udword anUdword;
			anUdword = strtoul((char*)&aTemp,0,0);
			*(aForm + aDestIndex++) = (char)anUdword;
			break;
		default:
			*(aForm + aDestIndex++) = aChar;
			break;
		}
	}
	*(aForm + aDestIndex++) = '\0';
	return aForm;
}

char* HTTPServer::findPathName(char* str)
{
	char* firstPos = strchr(str, ' ');
	firstPos++;
	char* lastPos = strchr(firstPos, ' ');
	char* thePath = 0;

	if ((lastPos - firstPos) == 1) {
		// Is / only
		thePath = 0;
	} else {
		// Is an absolute path, skip first /
		thePath = extractString((char*)(firstPos+1),lastPos-firstPos);
		if ((lastPos = strrchr(thePath, '/')) != 0) {
			// Found a path, insert -1 as terminator
			*lastPos = '\xff';
			*(lastPos+1) = '\0';
			while ((firstPos = strchr(thePath, '/')) != 0) {
				// Insert -1 as separator
				*firstPos = '\xff';
			}
		} else {
			// Is /index.html
			delete thePath;
			thePath = 0;
		}
	}
		
	return thePath;
}

/************** END OF FILE http.cc *************************************/
