#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
	
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofSetupOpenGL(1024,800, OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowTitle("ArtBox Controlpanel");

	// this kicks off the running of my app
	ofRunApp(new testApp);
	
}
