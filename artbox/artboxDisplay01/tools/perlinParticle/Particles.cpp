/*
 *  Particles.cpp
 *  openFrameworks
 *
 *  Created by rui madeira on 6/30/08.
 *
 */
#include "perlin.h"
#include "Particles.h"

Particles::Particles(ofxVec3f _pos, ofxVec3f _vel){
	pos = _pos;
	vel = _vel;
	noise = new Perlin(1, 0.5, 1, ofRandom(0,1000));	
	life = (int)ofRandom(100, 200);
	counter = 0;
	switch ((int)ofRandom(3,0)) {
		case 0:
			r = 179; g = 288; b = 0;
			break;
		case 1:
			r = 255; g = 128; b = 0;
			break;
		case 2:
			r = 0; g = 255; b = 255;
			break;
		default:
			r = 0; g = 0; b = 0;
			break;
	}
	
	length = (int) ofRandom(80,120);
}

Particles::~Particles(){}


void Particles::move(vector<Finger> fingers){
	history.push_back(pos);
	if(history.size() > length){
		history.erase(history.begin());
	}
	float damp = 0.2;
	life--;
	
	//divider os the particles coordinates. the bigger this is closer the coordinates will be to each other
	//making for smoother transitions between numbers (smoother flow field)
	int div = 500;
	
	//to scale up the perlin vector
	int mult = 1;
	
	//the range of the random vector
	int step = 0;
	
	//this perlin noise function initialized the way it has been here ((4, 4, 1, time(NULL))) will give numbers between -1 and 1
	//(the noise function in processing will give result between 0 and 1).
	//because we're using it to calculate the rotation of a velocity vector we multiply by TWO_PI so to get
	//values between -TWO_PI and TWO_PI. this will repeat values (HALF_PI is the same as -HALF_PI, TWO_PI is the same as 0, and so on,
	//but since the values of the perlin noise will rarely be close to 1 or -1 i think (but i'm not sure) this will give a more
	//homogeneous result.
	//the counter variable is there to continously shift the flow field.
	float radXZ = noise->Get((pos.x+counter)/div, pos.y/div) * TWO_PI;
	float radY = noise->Get((pos.y+counter)/div, pos.x/div) * TWO_PI;
	
	ofxVec3f perlinVec;
	
	
	// i kinda understand what goes on in the next 3 lines, but its hard to explain, but its basically using some trigonometry to calculate
	// the sides of the triangles of the angles we calculates using the noise function (radXZ and radY). and multiplying it because sin and cos
	//will alwways throw numbers between -1 and 1
	perlinVec.x = cos(radXZ)*mult;
	
	//sin is negative because y increases going down.
	perlinVec.y = -sin(radY)*mult;
	perlinVec.z = sin(radXZ)*mult;
	
	perlinVec.normalize();
	perlinVec *= 2;
	
	ofxVec3f randomVec = ofxVec3f(10,ofRandom(-1.0,1.0),ofRandom(-1.0,1.0));
	
	ofxVec3f fingeVec = ofxVec3f();
	for(int i=0;i<fingers.size();i++){
		float dist = fingers[i].loc.distance(ofxPoint2f(pos.x/ofGetWidth(), pos.y/ofGetHeight()));
		if(dist < 0.2){
			float factor = -(dist/0.2)*(dist/0.2)+1;

			fingeVec += -(fingers[i].loc - ofxPoint2f(pos.x/ofGetWidth(), pos.y/ofGetHeight()))*factor;
		}
		
	}
	
	vel += randomVec;
	vel += perlinVec; 
	vel += fingeVec*100; 
	
	
	//damp is just  way of scalling down the velocity vector. a simple way of simulating friction
	vel *= damp;
	
	pos += vel;

}

void Particles::draw(){
	glPushMatrix();
//	glTranslatef(pos.x, pos.y, pos.z);
	glBegin(GL_QUAD_STRIP);
	float s = 0;
	float e = 0;
	ofSetColor(0, 0, 0,128);

	for(int i = 0; i<history.size()-1; i++){
		ofxVec3f perp = history[i+1]-history[i];
		ofxVec3f hat =  ofxVec3f(-perp.y, perp.x, 0);
		hat.normalize();

		hat *= s/2.0+2;

		//cout<<(history[i]+hat).x<<" "<<hat.y<<endl;
		glVertex3f((history[i]-hat).x, (history[i]-hat).y, 0);
		glVertex3f((history[i]+hat).x, (history[i]+hat).y, 0);
		
		if(s < 9 && e == 0){
			s += (10-s)*0.2;
		} else if (e == 0){
			e = i+5;
		}
		if(i+e > history.size()){
			s -= (10-s)*0.2;
		}

		//ofCircle(history[i].x, history[i].y, 10);
	}
	glEnd();
	
	glBegin(GL_QUAD_STRIP);
	s = 0;
	e = 0;
	ofSetColor(r, g, b);
	for(int i = 0; i<history.size()-1; i++){
		ofxVec3f perp = history[i+1]-history[i];
		ofxVec3f hat =  ofxVec3f(-perp.y, perp.x, 0);
		hat.normalize();		
		hat *= s/2.0;		
		glVertex3f((history[i]-hat).x, (history[i]-hat).y, 0);
		glVertex3f((history[i]+hat).x, (history[i]+hat).y, 0);
		if(s < 9 && e == 0){
			s += (10-s)*0.2;
		} else if (e == 0){
			e = i+5;
		}
		if(i+e > history.size()){
			s -= (10-s)*0.2;
		}
	}
	glEnd();
	

	glPopMatrix();
	
}

