#include "toolIncludes.h"
#include "finger.h"

class ToolsController{
public:
	vector<Finger>		fingers;
	vector<Tool*>		tools;
	
	
	PerlinParticle perlinParticle;
	MidiInstrument midiInstrument;
	
	ToolsController() {
		tools.push_back(&perlinParticle);
		tools.push_back(&midiInstrument);
	}
	
	void setup(){
		for(int i=0;i<tools.size();i++){
			tools[i]->fingers = &fingers;
		}
	}
	
	void update(ofxOscSender * sender){
		for(int i=0;i<tools.size();i++){
			tools[i]->toolUpdate(sender);
		}
	}
	void draw(){
		for(int i=0;i<tools.size();i++){
			tools[i]->toolDraw();
		}
	}
	
	void handleIncommingOsc(ofxOscMessage *m){
		for(int i=0;i<tools.size();i++){
			for(int u=0;u<tools[i]->sharedVariables.size();u++){
				tools[i]->sharedVariables[u].handleOsc(m, tools[i]->toolName);
			}
		}
	}
	

	
};

