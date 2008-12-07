#define OF_ADDON_USING_OFXMIDI

#include "tool.h"
#include "ofAddons.h"
#include "finger.h"

#ifndef _OFX_midi_H_
#define _OFX_midi_H_

class MidiNode {
public:
	//	float 
	int x; 
	float y;
	
	int age;
	int id ;
};

class MidiInstrument : public Tool {
public:
	MidiInstrument();
	virtual int  update();
	virtual int  draw();	
	
	virtual int loadControlPanel(ofxGuiPanel* panel, ofxGuiListener* listener);
	virtual int handleGui(int parameterId, int task, void* data, int length, ofxOscSender *sender);
	virtual int oscMessage(ofxOscMessage* m);
	
	bool displayActive;
	
	ofxMidiOut * midi;
	
	float timeX;
	bool nodeOn;
	vector<MidiNode> nodes;
	
	float speed;
};



#endif