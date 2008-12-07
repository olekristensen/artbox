#define OF_ADDON_USING_OFXGUI
#define OF_ADDON_USING_OFXOSC

#include "ofMain.h"
#include "ofAddons.h"
#include "finger.h"
#include "sharedVariable.h"

#ifndef _OFX_TOOL_H_
#define _OFX_TOOL_H_



enum
{
	kParameter_Panel1,
	
	kParameter_perlinParticle_active,
	
	kParameter_midiInstrument_active,
	kParameter_midiInstrument_speed,

};


class Tool {
public:
	float opacity;
	string toolName;
	bool active;
	
	int  toolUpdate(ofxOscSender * sender){
		for(int i=0;i<sharedVariables.size();i++){
			sharedVariables[i].update(sender, toolName);
		}
		update();
	}
	int  toolDraw(){draw();}

	virtual int  update(){return(0);}
	virtual int  draw(){return(0);}
	
	vector<Finger>	* fingers;
	vector<SharedVariable>	sharedVariables;

	

	
	virtual int loadControlPanel(ofxGuiPanel* panel, ofxGuiListener* listener){return(0);}
	virtual int handleGui(int parameterId, int task, void* data, int length, ofxOscSender * sender){return(0);}
	void handleOsc(ofxOscMessage *m){
		for(int i=0;i<sharedVariables.size();i++){
			sharedVariables[i].handleOsc(m, toolName);
		}
		oscMessage(m);
	}
	virtual int oscMessage(ofxOscMessage* m){return 0;}

	
};

#endif