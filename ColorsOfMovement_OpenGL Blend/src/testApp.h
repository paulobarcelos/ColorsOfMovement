#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
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
	void				keyPressed (int key);
	
	ofVideoGrabber 		capture;	
	ColorsOfMovement	cm;
	
	ofImage				logo;
	ofImage				splash;
	
	
};
#endif