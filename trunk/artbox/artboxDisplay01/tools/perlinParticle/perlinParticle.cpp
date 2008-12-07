#include "perlinParticle.h"


PerlinParticle::PerlinParticle(){
	addParticles = true;
	addParticleTimer = 0;
	active = false;
	toolName = "Perlin Particle";
	
	displayActive = false;
	sharedVariables.push_back(SharedVariable(&displayActive, "active"));
	
}

int PerlinParticle::update(){	
	if(displayActive){
		emitter.move(ofGetWidth()/2.0, ofGetHeight()/2.0);
	
		addParticleTimer--;
		if(addParticleTimer <= 0){
			if(particles.size() < MAX_PARTICLES){
				int step = 0;
				ofxVec3f iniVel = ofxVec3f(ofRandom(0,20), ofRandom(-step, step), ofRandom(-step, step));
				particles.push_back(Particles(ofxVec3f(-30,ofRandom(0,ofGetHeight())),iniVel));
				addParticleTimer = ofRandom(1,20);
			}
		}

		vector<Finger> tFingers = *fingers;

		for(int i=0; i<particles.size(); i++){
			particles[i].move(tFingers);
			if(particles[i].history[0].x > ofGetWidth()){
				particles.erase(particles.begin() +i);
			}
		}
	}
}

int PerlinParticle::draw(){
	if(displayActive){
		for(int i=0; i<particles.size(); i++){
			particles[i].draw();
		}		
	}
}

int PerlinParticle::loadControlPanel(ofxGuiPanel* panel, ofxGuiListener* listener){
	panel->addButton(kParameter_perlinParticle_active, "Active", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, displayActive, kofxGui_Button_Switch);
	return 1;
}

int PerlinParticle::handleGui(int parameterId, int task, void* data, int length, ofxOscSender * sender){
	switch(parameterId)
	{		
		case kParameter_perlinParticle_active:
			if(task == kofxGui_Set_Bool)
				displayActive = *(bool*)data;
			break;
	}
}

int PerlinParticle::oscMessage(ofxOscMessage *m){
}