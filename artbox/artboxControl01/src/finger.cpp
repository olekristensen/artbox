#include "finger.h"
#include "ofConstants.h"

void Finger::update(){
	loc.x += vel.x;
	loc.y += vel.y;
}

void Finger::move(float x, float y){
	ofxPoint2f a;
	a.x = (x-loc.x)*0.2;
	a.y = (y-loc.y)*0.2;
	vel *= 0.3;
	vel += a;
}

void Finger::debugDraw(){
	ofSetColor(255, 0, 0);
	float s;
	float t = 100.0;
	if(age <t ){
		s =  (age)/(t)*10.0;
	} else 
		s = 10;
	ofCircle(loc.x*ofGetWidth(), loc.y*ofGetHeight(), s);	
	ofSetColor(0, 255, 0);
	ofLine(loc.x*ofGetWidth(), loc.y*ofGetHeight(),(loc.x+vel.x*100.0)*ofGetWidth(), (loc.y+vel.y*100.0)*ofGetHeight());
	
}
