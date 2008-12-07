#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(1024,600, OF_WINDOW);			// <-------- setup the GL context
		ofSetWindowPosition(-1024, 0);
	ofToggleFullscreen();
	//	glutFullScreen();

	// this kicks off the running of my app
	ofRunApp(new testApp);
	
}
