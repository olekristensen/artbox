/*
 *  finger.h
 *  openFrameworks
 *
 *  Created by Vision4 on 25/09/08.
 *  Copyright 2008 Vision4. All rights reserved.
 *
 */



#ifndef _OFX_FINGER_H_
#define _OFX_FINGER_H_
#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
#include "ofAddons.h"
class Finger {
	public:
	
	ofxPoint2f loc;
	ofxPoint2f vel;
	int timeOut;
	int id;
	int age;
	
	void move(float x, float y);
	void debugDraw();
	
	void update();
	
}; 
#endif
