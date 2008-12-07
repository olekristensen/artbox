#include "testApp.h"
#include "perlin.h"



//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0, 0, 0); 
	ofSetVerticalSync(true);
	
	//enable additive blending to get glowy stuff...
	ofEnableSmoothing();
	ofEnableAlphaBlending();

	receiver.setup(8001);
	receiverTUIO.setup(7770);

	sender.setup("127.0.0.1", 8000);
	
	contr.setup();
}

//--------------------------------------------------------------
void testApp::update(){
		
	oscPingTimer ++;
	if(oscPingTimer > 100){
		oscPingTimer = 0;
		ofxOscMessage m;
		m.setAddress( "/ping/framerate" );
		m.addIntArg( ofGetFrameRate() );
		sender.sendMessage( m );
	}
	
	// check for waiting messages
	while( receiverTUIO.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiverTUIO.getNextMessage( &m );		
		
		if ( strcmp( m.getAddress(), "/tuio/2Dcur" ) == 0 )
		{
			sender.sendMessage( m );
			if ( strcmp( m.getArgAsString( 0 ), "set" ) == 0 )
			{
				bool found = false;
				for(int i=0; i< contr.fingers.size(); i++){
					if(contr.fingers[i].id == m.getArgAsInt32( 1 )){
						contr.fingers[i].move(m.getArgAsFloat(2), m.getArgAsFloat(3));
						contr.fingers[i].timeOut = 0;
						found = true;
					}
					else if(contr.fingers[i].loc.distance(ofxPoint2f(m.getArgAsFloat(2), m.getArgAsFloat(3)))< 0.03){
						contr.fingers[i].move(m.getArgAsFloat(2), m.getArgAsFloat(3));
						contr.fingers[i].timeOut = 0;
						contr.fingers[i].id = m.getArgAsInt32( 1 );
						found = true;
					}
				}
				if(!found){
					Finger nFing;
					nFing.loc.x =m.getArgAsFloat(2) ;
					nFing.loc.y =m.getArgAsFloat(3) ;
					nFing.id =  m.getArgAsInt32( 1 );
					nFing.timeOut = 0;
					nFing.age = 0;
					contr.fingers.push_back(nFing);
				}
			}		
			else if ( strcmp( m.getArgAsString( 0 ), "alive" ) == 0 ) {
				if(m.getNumArgs()>1){
					for(int i=0; i< contr.fingers.size(); i++){
						if(contr.fingers[i].id == m.getArgAsInt32( 1 )){
							contr.fingers[i].timeOut = 0;
							break;						
						}
					}				
				}
			}
		}
	}
	
	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );	
		
		for(int i=0;i<contr.tools.size();i++){
			contr.tools[i]->handleOsc(&m);
		}
		
		if ( strcmp( m.getAddress(), "/control/mouse" ) == 0 )
		{
			bool found = false;
			for(int i=0; i< contr.fingers.size(); i++){
				if(contr.fingers[i].id == -1){
					contr.fingers[i].move(m.getArgAsFloat(0), m.getArgAsFloat(1));
					contr.fingers[i].timeOut = 0;
					found = true;
				}
			}
			if(!found){
				Finger nFing;
				nFing.loc.x =m.getArgAsFloat(0) ;
				nFing.loc.y =m.getArgAsFloat(1) ;
				nFing.id =  -1;
				nFing.timeOut = 0;
				nFing.age = 0;
				contr.fingers.push_back(nFing);
			}
		}		
	}
	
	for(int i=0; i< contr.fingers.size(); i++){
		/*for(int u=particles.size()-1; u>=0; u--){
		//	float x = contr.fingers[i].loc.x - particles[u].loc.x;
			float y = contr.fingers[i].loc.y - particles[u].loc.y;
			if((x>-0.1 && x<0.1) && (y>-0.1 && y<0.1)){
			//	float d = contr.fingers[i].loc.distance(particles[u].loc);
				//	cout<<d<<endl;
				/*if(particles[u].blue < 255)
					particles[u].blue += (0.2-d)*2.0;
				if(particles[u].green < 255)
					particles[u].green += (0.3-d)*10.0;
				if(particles[u].red < 255)
					particles[u].red += (0.2-d)*9.0;*/
				//particles[u].dir += contr.fingers[i].vel*0.005;
				//particles[u].dir += (contr.fingers[i].loc-	particles[u].loc)*0.004*(0.2-d);
				//		cout<<particles[u].red<<endl;
			//}
	//	}	*/	
		contr.fingers[i].timeOut++;
		contr.fingers[i].age ++;
		
		contr.fingers[i].update();
		if(contr.fingers[i].timeOut > ofGetFrameRate()/10.0){
			//cout<<"Delete "<<i<<" "<<contr.fingers[i].timeOut<<endl;
			contr.fingers.erase(contr.fingers.begin()+i);
		}
	}	
		
	contr.update(&sender);

	
}

//--------------------------------------------------------------
void testApp::draw(){
	contr.draw();
	
	for(int i=0; i<contr.fingers.size(); i++){
		ofSetColor(255, 0, 0);
		ofCircle(contr.fingers[i].loc.x *ofGetWidth(), contr.fingers[i].loc.y *ofGetHeight(), 10);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
mouseX = x;
mouseY = y;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
