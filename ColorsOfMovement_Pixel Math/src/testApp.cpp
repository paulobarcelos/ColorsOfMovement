#include "testApp.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::setup(){	
	ofSetVerticalSync(true);
	ofBackground(25, 28, 33);
	ofSetFullscreen(true);
	
	logo.loadImage("logo.png");
	splash.loadImage("splash.png");
	
	capture.setVerbose(true);
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
		cm.draw(0, 0, ofGetWidth(), ofGetHeight());
		
		// Draw logo
		ofEnableAlphaBlending();
		w = ofGetWidth()/5;
		h = w*((float)logo.height/(float)logo.width);
		x = ofGetWidth()-w-w/8;
		y =ofGetHeight()-h-w/8;
		logo.draw(x,y,w,h);
		ofPopMatrix();
		ofDisableAlphaBlending();
	}
	else
	{
		// Draw splash
		ofEnableAlphaBlending();
		ofPushMatrix();
		w = ofGetWidth()/3*2;
		h = w*((float)splash.height/(float)splash.width);
		x = ofGetWidth()/2-w/2;
		y = ((float)ofGetHeight() - h)/2.0f;
		splash.draw(x,y,w,h);
		ofPopMatrix();
		ofDisableAlphaBlending();
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
}
