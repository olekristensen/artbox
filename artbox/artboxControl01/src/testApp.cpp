#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20, 20, 20); 
	ofSetFrameRate(30);	

	receiver.setup(8000);
	sender.setup("127.0.0.1", 8001);
	
	connectionTimer = -1;
	mouseIsPressed = false;
	activateTool = -1;

	fontBig.loadFont("Arial Black.ttf", 16, true, true);
	fontSmall.loadFont("Arial Black.ttf", 10, true, true);
	
	gui	= ofxGui::Instance(this);
	gui->mGlobals->mCoverColor = ofRGBA(20, 20, 20,255);	
	toolsPanel = gui->addPanel(kParameter_Panel1, "tool", 340, monitorY, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	gui->forceUpdate(true);	
	gui->activate(true);
}

//--------------------------------------------------------------
void testApp::update(){	
	
	for(int i=0;i<tool.tools.size();i++){
		for(int u=0;u<tool.tools[i]->sharedVariables.size();u++){
			 tool.tools[i]->sharedVariables[u].update(&sender, tool.tools[i]->toolName);
		}
	}
	
	
	if(connectionTimer != -1){
		connectionTimer ++;
	}
	if(connectionTimer > 200){
		connectionTimer = -1;
	}
	
	// check for waiting messages
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );		
		cout<<"got message: "<<m.getAddress()<<endl;
		
		tool.handleIncommingOsc(&m);
		
		if ( strcmp( m.getAddress(), "/ping/framerate" ) == 0 )
		{
			// both the arguments are int32's
			connectionTimer = 0;
			frameRate = m.getArgAsInt32(0);
		}

		if ( strcmp( m.getAddress(), "/tuio/2Dcur" ) == 0 )
		{
			if ( strcmp( m.getArgAsString( 0 ), "set" ) == 0 )
			{
				bool found = false;
				for(int i=0; i< tool.fingers.size(); i++){
					if(tool.fingers[i].id == m.getArgAsInt32( 1 )){
						tool.fingers[i].move(m.getArgAsFloat(2), m.getArgAsFloat(3));
						tool.fingers[i].timeOut = 0;
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
					tool.fingers.push_back(nFing);
				}
			}		
			else if ( strcmp( m.getArgAsString( 0 ), "alive" ) == 0 ) {
				if(m.getNumArgs()>1){
					for(int i=0; i< tool.fingers.size(); i++){
						if(tool.fingers[i].id == m.getArgAsInt32( 1 )){
							tool.fingers[i].timeOut = 0;
							break;						
						}
					}				
				}
			}
		}
	}
	

	for(int i=0; i< tool.fingers.size(); i++){
		tool.fingers[i].timeOut++;
		tool.fingers[i].age ++;		
		tool.fingers[i].update();
		if(tool.fingers[i].timeOut > 30){
			tool.fingers.erase(tool.fingers.begin()+i);
		}
	}	
	
	if(activateTool != -1){
		for(int u=0; u<tool.tools.size();u++){
			tool.tools[u]->active = false;
		}
		tool.tools[activateTool]->active = true;
		toolsPanel->mObjects.clear();
		toolsPanel->mObjHeight = 0;
		toolsPanel->mObjWidth = 0;
		toolsPanel->init(kParameter_Panel1, tool.tools[activateTool]->toolName, 340, monitorY, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
		tool.tools[activateTool]->loadControlPanel(toolsPanel, this);	
		activateTool = -1;
	}
	
	
	//--Monitor
	if(mouseX>monitorX && mouseX < monitorX+300 && mouseY > monitorY && mouseY < monitorY + 300){
		mouseOverMonitor = true;

		if(mouseIsPressed){

			ofxOscMessage m;
			m.setAddress( "/control/mouse" );
			m.addFloatArg((mouseX-monitorX)/300.0);
			m.addFloatArg((mouseY-monitorY)/300.0);
			sender.sendMessage( m );
		}
	} else {
		mouseOverMonitor = false;
	}

	
		
}

//--------------------------------------------------------------
void testApp::draw(){
	if(connectionTimer == -1){
		//No connection
		ofSetColor(255, 255, 255);
		string s = "Waiting for display...";
		fontBig.drawString(s, ofGetWidth()/2.0-fontBig.stringWidth(s)/2.0 , ofGetHeight()/2.0 );

	} else {
		//--Top 
		ofSetColor(255, 255, 255);
		fontBig.drawString("ArtBox Controlpanel", 20, 20);
		fontSmall.drawString("Framerate: "+ofToString(frameRate, 0), ofGetWidth()-150, 20);
		ofSetColor(80,80,80);
		ofLine(0, 30, ofGetWidth(), 30);
		
		//Monitor
		ofSetColor(120,120,120);
		glPushMatrix();

		glTranslated(monitorX, monitorY, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(300, 0, 0);
		glVertex3f(300, 300, 0);
		glVertex3f(0, 300, 0);
		glEnd();
		
		
		for(int i=0;i<tool.fingers.size();i++){
			ofCircle(tool.fingers[i].loc.x*300, tool.fingers[i].loc.y*300, 5);
		}
		
		glPopMatrix();
		ofSetColor(80,80,80);
		if(mouseOverMonitor){	
			if(mouseIsPressed)
				ofSetColor(180, 0, 0);
			ofLine(monitorX, mouseY, monitorX+300, mouseY);
			ofLine(mouseX, monitorY, mouseX, monitorY+300);
		}
		
		//Tool list
		int y = monitorY+320;
		for(int i=0;i<tool.tools.size(); i++){
			glPushMatrix();
			glTranslated(20, y, 0);

			if(tool.tools[i]->active || (mouseX > 20 && mouseX < 170 && mouseY > y && mouseY < y+20)){
				ofFill();
				ofSetColor(120, 120, 120);
				ofRect(0,0,150,20);
				ofSetColor(0, 0, 0);
				if(mouseIsPressed && !tool.tools[i]->active){
					activateTool = i;
				}
			}
			else{
				ofNoFill();
				ofSetColor(120, 120, 120);
				ofRect(0,0,150,20);
			}
			
			fontSmall.drawString(tool.tools[i]->toolName, 10, 12);
			glPopMatrix();
			y+=25;
		}
		
		gui->draw();
	//	contr.draw();


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

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	gui->mouseDragged(x, y, button);	

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	mouseIsPressed = true;
	gui->mousePressed(x, y, button);	

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	mouseIsPressed = false;
	gui->mouseReleased(mouseX, mouseY, 0);	

}


void testApp::handleGui(int parameterId, int task, void* data, int length)
{
	for(int i=0;i<tool.tools.size();i++){
		tool.tools[i]->handleGui(parameterId, task, data, length, &sender);
	}
	
}