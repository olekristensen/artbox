/*
 *  Emitter.h
 *  openFrameworks
 *
 *  Created by rui madeira on 6/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EMITTER_H
#define EMITTER_H

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
#include "ofAddons.h"

class Emitter{
public:
	ofxVec3f pos;
	Emitter();
	~Emitter();
	
	void move(int _mouseX, int _mouseY);
	void draw();
};	

#endif