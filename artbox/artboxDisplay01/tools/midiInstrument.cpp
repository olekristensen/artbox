/*
 *  midiInstrument.cpp
 *  artboxDisplay
 *
 *  Created by Vision4 on 05/12/08.
 *  Copyright 2008 Vision4. All rights reserved.
 *
 */

#include "midiInstrument.h"


MidiInstrument::MidiInstrument(){

	midi = new ofxMidiOut();
	midi->sendNoteOff(80,100);
	toolName = "Midi Instrument";
	displayActive = false;
	speed = 0.1;
	sharedVariables.push_back(SharedVariable(&displayActive, "active"));
	sharedVariables.push_back(SharedVariable(&speed, "speed"));
	
}

int MidiInstrument::update(){	
	if(displayActive){

		//midi->sendNoteOn(80,100);
		timeX += speed*ofGetFrameRate();
		if(timeX > ofGetWidth()){
			timeX = 0;
		}
		vector<Finger> tFingers = *fingers;
		for(int i=0;i<tFingers.size();i++){
			if(tFingers[i].loc.x*ofGetWidth() > timeX-10 && tFingers[i].loc.x*ofGetWidth() < timeX+10 ){
				bool nodeFound = false;
				for(int u=0;u<nodes.size();u++){
					if(nodes[u].id == tFingers[i].id){
						nodeFound = true;
					}
				} 
				
				if(!nodeFound){
					cout<<"new node"<<endl;
					MidiNode node;
					node.x = tFingers[i].loc.x*ofGetWidth();
					node.y = tFingers[i].loc.y;
					node.age = 0;	
					node.id = tFingers[i].id;
					nodes.push_back(node);
					nodeOn = true;
					midi->sendNoteOn(40+40.0*node.y,50);
					cout<<node.y<<endl;
				}
			}
		}
		for(int u=0;u<nodes.size();u++){
			nodes[u].age++;
			if(nodes[u].age > 20){
				midi->sendNoteOff(40+40.0*nodes[u].y,0);
				cout<<"off"<<endl;
				nodes.erase(nodes.begin()+u);
			}
		}
		if(nodeOn){
			//midi->sendNoteOff(80,100);
		}
	}
}

int MidiInstrument::draw(){	
	if(displayActive){

		for(int u=0;u<nodes.size();u++){
			ofSetColor(255, 0, 0,((20-nodes[u].age)/20.0)*255);
			ofNoFill();
			for(int i=0;i<10;i++){
				ofCircle(nodes[u].x, nodes[u].y*ofGetHeight(), nodes[u].age*5-i);
			}
			ofFill();
		}	

		ofSetColor(200, 200, 255);
		ofLine(timeX, 0, timeX, ofGetHeight());
		ofLine(timeX-1, 0, timeX-1, ofGetHeight());
		ofLine(timeX+1, 0, timeX+1, ofGetHeight());
	
	}
}


int MidiInstrument::loadControlPanel(ofxGuiPanel* panel, ofxGuiListener* listener){
	panel->addButton(kParameter_midiInstrument_active, "Active", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, displayActive, kofxGui_Button_Switch);
	panel->addSlider(kParameter_midiInstrument_speed, "Speed", 110, OFXGUI_SLIDER_HEIGHT, 0.0f, 0.5f, speed, kofxGui_Display_Float4, 0);
	return 1;
}

int MidiInstrument::handleGui(int parameterId, int task, void* data, int length, ofxOscSender * sender){
	switch(parameterId)
	{		
		case kParameter_midiInstrument_active:
			if(task == kofxGui_Set_Bool){
				displayActive = *(bool*)data;
				cout<<"set active"<<endl;
			}
			break;
		
		case kParameter_midiInstrument_speed:
			if(task == kofxGui_Set_Float){
				speed = *(float*)data;
			}
			break;
	}
}


int MidiInstrument::oscMessage(ofxOscMessage *m){
}