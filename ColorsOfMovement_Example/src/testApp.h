#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ColorsOfMovement.h"
#include "ColorsOfMovementSettings.h"

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class testApp : public ofBaseApp{
	
public:
	
	void	setup();
	void	update();
	void	draw();
	void	keyPressed (int key);
	
	ofVideoGrabber				capture;	
	ColorsOfMovement			cm;
	ColorsOfMovementSettings	cmSettings;
};
#endif