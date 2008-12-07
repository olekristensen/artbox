#ifndef _TEST_APP
#define _TEST_APP

#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXOSC

#include "ofMain.h"
#include "ofAddons.h"
#include "toolsController.h"
#include "finger.h"




class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	
		ToolsController contr;
		
		ofxOscReceiver	receiver;
		ofxOscReceiver	receiverTUIO;

		ofxOscSender sender;
	
		int	oscPingTimer;		
};

#endif
	
