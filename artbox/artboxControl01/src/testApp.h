#ifndef _TEST_APP
#define _TEST_APP

//#define OF_ADDON_USING_OFXDIRLIST
//#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXOSC
#define OF_ADDON_USING_OFXGUI

#include "ofMain.h"
#include "ofAddons.h"
#include "toolsController.h"


class testApp : public ofSimpleApp, public ofxGuiListener{
	enum
	{
		kParameter_Panel1,
};	
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
	
		void handleGui(int parameterId, int task, void* data, int length);

		ofxGui*	gui;

		int connectionTimer;
		ofxOscReceiver	receiver;
		ofxOscSender sender;
		float frameRate;
		bool mouseIsPressed;
		static const int monitorX=20;
		static const int monitorY=50;
		bool mouseOverMonitor;

		ofTrueTypeFont		fontBig;
		ofTrueTypeFont		fontSmall;
		
	
		//Monitor coordinates


		

		ToolsController tool;
		ofxGuiPanel* toolsPanel;
		int activateTool;
		//ToolsController contr;

		
};

#endif
	
