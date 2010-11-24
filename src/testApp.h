#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSmartCapture.h" // get it at https://github.com/paulobarcelos/ofxSmartCapture
#include "ofxDrawingUtils.h" // now included in the ColorsOfMovement repo, soon should have it's own. BIG thanks to the author Oriol Ferrer. (www.uri.cat)

#include "ColorsOfMovement.h"

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class testApp : public ofBaseApp{
	
public:
	void				setup();
	void				update();
	void				draw();
	void				onCameraConnection (ofxSmartCaptureEventArgs &args);
	void				keyPressed (int key);
	
	ofxSmartCapture		capture;	
	ColorsOfMovement	cm;
	
	ofImage				logo;
	ofImage				splash;
	
	
};
#endif