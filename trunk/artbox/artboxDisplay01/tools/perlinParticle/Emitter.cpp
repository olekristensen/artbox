/*
 *  Emitter.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/30/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "Emitter.h"

Emitter::Emitter(){

}

Emitter::~Emitter(){}

void Emitter::move(int _mouseX, int _mouseY){
	ofxVec3f targetPos = ofxVec3f(_mouseX, _mouseY, 0);
//	pos.interpolated(targetPos, 0.2);
	pos = targetPos;
}

void Emitter::draw(){
	ofSetColor(40, 40, 150);
	ofCircle(pos.x, pos.y, 10);

}