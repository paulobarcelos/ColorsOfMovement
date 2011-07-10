#include "testApp.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::setup(){
	
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(0, 0, 0);
	//ofSetFullscreen(true);
	
	logo.loadImage("logo.png");
	splash.loadImage("splash.png");
	
	capture.setVerbose(true);
	capture.setDeviceID(1);
	capture.initGrabber(640,480);
	
	cm.setup(640, 480);
}

///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::update(){
	capture.grabFrame();
	
	if (capture.isFrameNew())
		cm.update(capture.getPixels());
	
	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::draw(){
	
	float w,h,x,y;
	if(cm.isReady())
	{
		cm.draw(0, 0);
		/*ofDrawImageInRect( &(cm.tex),											//original image pointer
							ofRectangle( 0,0, ofGetWidth(), ofGetHeight()),		//size and location of the image
							false,												//rotate 90
							true,												//flip horizontal
							VERTICAL_CENTER,									//vertical align
							HORIZONTAL_CENTER									//horizontal align
							);*/
		
	}
	

}
///////////////////////////////////////////////////////////////////////////////////
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::keyPressed(int key){
	
	if (key=='s')
		capture.videoSettings();
	
	if (key==' ')
		ofToggleFullscreen();
		
	if (key=='-')
		cm.setStoredFrames( cm.getStoredFrames() - 1 );
	
	if (key=='+')
		cm.setStoredFrames( cm.getStoredFrames() + 1 );
	
	if (key == 'w') 	
		cm.saveSettings();
	
	if (key == 'r') 
		cm.loadSettings(); 
	
	printf( "%d frames\n", cm.getStoredFrames() );
	
}
