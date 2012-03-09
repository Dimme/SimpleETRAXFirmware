#ifndef http_hh
#define http_hh

class HTTPServer : public Job
{
public:

	HTTPServer(TCPSocket* theSocket);
	void doit();
	
	byte* headReq(char* theHeader, udword &contentLength, bool withBody);
	void getReq(char* theHeader);
	void postReq(char* theHeader, char* theBody);
	
	void sendError(uword theError, bool withBody);
	
	char* extractString(char* thePosition, udword theLength);
	udword contentLength(char* theData, udword theLength);
	char* decodeBase64(char* theEncodedString);
	char* decodeForm(char* theEncodedForm);
	char* findPathName(char* str);
	
	enum {
		GET = 1,
		POST = 2,
		HEAD = 3	
	};
	
	enum {
		HTML = 4,
		JPEG = 5,
		GIF = 6	
	};
	
private:
	// Pointer to the application associated with this job.
	TCPSocket* mySocket;
};

#endif
