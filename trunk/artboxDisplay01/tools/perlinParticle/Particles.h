/*
 *  Particles.h
 *  openFrameworks
 *
 *  Created by rui madeira on 6/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef PARTICLES_H
#define PARTICLES_H

#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
#include "ofAddons.h"
#include "perlin.h"
#include "finger.h"


class Particles{
public:
	ofxVec3f pos, vel;
	int life;
	int counter;
	Perlin * noise;
	Particles(ofxVec3f _pos, ofxVec3f _vel);
	~Particles();
	int r,g,b;
	vector <ofxVec3f> history;

	
	void move(vector<Finger> fingers);
	void draw();
	
	int length;
};


#endif
