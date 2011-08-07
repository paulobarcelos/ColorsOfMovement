/*
 *  ColorsOfMovementSettings.h
 *  ColorsOfMovement
 *
 *  Created by Paulo Barcelos on 7/26/11.
 *  Copyright 2011 paulobarcelos.com. All rights reserved.
 *
 */

#ifndef _COLORS_OF_MOVEMENT_SETTINGS
#define _COLORS_OF_MOVEMENT_SETTINGS

#include "ofMain.h"
#include "ColorsOfMovement.h"
#include "ofxKeyboardSettings.h"

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ColorsOfMovementSettings {
	
public:
	ColorsOfMovementSettings();
	~ColorsOfMovementSettings();
	void				setup(ColorsOfMovement* cm, int accessKey = 'c', string label = "Colors_of_Movement");
	void				keyPressed(int key);	
	void				draw(float x, float y);
	
private:
	
	ColorsOfMovement*	cm;
	ofxKeyboardSettings	settings;	
};
#endif