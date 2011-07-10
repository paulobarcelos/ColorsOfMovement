#include "testApp.h"

///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::setup(){
	
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofBackground(25, 28, 33);
	ofSetFullscreen(true);
	
	logo.loadImage("logo.png");
	splash.loadImage("splash.png");
	
	//ofAddListener(capture.events.connectionEvt, this, &testApp::onCameraConnection);
	
	//capture.startCapture(640, 480);
	capture.setVerbose(true);
	capture.setDeviceID(1);
	capture.initGrabber(640,480);
	
	cm.setup(640, 480);
}
/*///////////////////////////////////////////////////////////////////////////////////
// onConnection -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::onCameraConnection(ofxSmartCaptureEventArgs &args){
	cm.setup(args.captureSize.x, args.captureSize.y);
}*/
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void testApp::update(){
	/*capture.update();
	
	if (capture.isCameraAvailable() && capture.isFrameNew())
		cm.update(capture.getPixels());*/
	
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
		ofDrawImageInRect( &(cm.tex),											//original image pointer
							ofRectangle( 0,0, ofGetWidth(), ofGetHeight()),		//size and location of the image
							false,												//rotate 90
							true,												//flip horizontal
							VERTICAL_CENTER,									//vertical align
							HORIZONTAL_CENTER									//horizontal align
							);
		
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
	
	if (key == 'w') 	
		cm.saveSettings();
	
	if (key == 'r') 
		cm.loadSettings(); 
	
	printf( "%d frames\n", cm.getStoredFrames() );
	
}
