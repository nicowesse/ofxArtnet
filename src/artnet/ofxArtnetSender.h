#pragma once
#include "ofxArtnetProtocol.h"
#include "ofxArtnetMessage.h"

class ofxArtnetSender : public ofxArtnetProtocol, public ofThread
{
public:
	ofxArtnetSender();
	ofxArtnetSender(const ofxArtnetSender& origin);

	~ofxArtnetSender();
  bool setup(const std::string& ipAdress, const std::uint16_t port = 6454);

	inline void enableThread(const float fps)
	{
		bThreadEnabled = true;
		framerate = fps;
		interval = 1000.0 / framerate;
		startThread();
	}

	inline void disableThread()
	{
		bThreadEnabled = false;
	}
	
	inline void setFps(const float fps) {
		if (bThreadEnabled) {
			framerate = fps;
			interval = 1000.0 / framerate;
		}
	}

	void sendArtnet(const ofxArtnetMessage& message);
  
  std::string getIP() const { return targetIp; }
	
protected:
	bool bThreadEnabled = false;
	void threadedFunction();

	std::string targetIp;
	short targetPort;
	float framerate = 40;
	float interval = 25;

    std::vector<ofxArtnetMessage> _messages;
	void createBuffer(const ofxArtnetMessage& message, std::vector<unsigned char>& data);
	void sendData(const ofxArtnetMessage& message);
};

