#include "tool.h"
#include "ofAddons.h"
#include "Particles.h"
#include "Emitter.h"

#include "finger.h"

#ifndef _OFX_perlinParticle_H_
#define _OFX_perlinParticle_H_

#define MAX_PARTICLES 200

class PerlinParticle : public Tool {
public:
	PerlinParticle();
	virtual int  update();
	virtual int  draw();	
	//	
	vector <Particles> particles;
	Emitter emitter;
	
	bool addParticles;
	float addParticleTimer;
	
	
	virtual int loadControlPanel(ofxGuiPanel* panel, ofxGuiListener* listener);
	virtual int handleGui(int parameterId, int task, void* data, int length, ofxOscSender *sender);
	virtual int oscMessage(ofxOscMessage* m);

	bool displayActive;

};

#endif