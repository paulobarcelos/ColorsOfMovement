/*
 *  ColorsOfMovementSettings.cpp
 *  ColorsOfMovement
 *
 *  Created by Paulo Barcelos on 7/26/11.
 *  Copyright 2011 paulobarcelos.com. All rights reserved.
 *
 */

#include "ColorsOfMovementSettings.h"

///////////////////////////////////////////////////////////////////////////////////
// Constructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ColorsOfMovementSettings::ColorsOfMovementSettings()
{
	cm = NULL;
}
///////////////////////////////////////////////////////////////////////////////////
// Destructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ColorsOfMovementSettings::~ColorsOfMovementSettings()
{	
	if(cm != NULL) delete cm;
}
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovementSettings::setup(ColorsOfMovement* cm, int accessKey, string label)
{	
	this->cm = cm;
	settings.setup(accessKey, label);
	
	settings.addProperty(cm, &ColorsOfMovement::getNumStoredFrames,
						 cm, &ColorsOfMovement::setNumStoredFrames,
						 "Number_of_stored_frames",
						 cm, &ColorsOfMovement::getNumStoredFramesMin,
						 cm, &ColorsOfMovement::getNumStoredFramesMax,
						 cm, &ColorsOfMovement::getNumStoredFramesStep,
						 CM_DEFAULT_NUM_STORED_FRAMES);
	
	settings.addProperty(cm, &ColorsOfMovement::getMode,
						 cm, &ColorsOfMovement::setMode,
						 "Mode",
						 cm, &ColorsOfMovement::getModeMin,
						 cm, &ColorsOfMovement::getModeMax,
						 cm, &ColorsOfMovement::getModeStep,
						 (int)CM_DEFAULT_MODE);
}
///////////////////////////////////////////////////////////////////////////////////
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovementSettings::keyPressed(int key)
{
	settings.keyPressed(key);
}
///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovementSettings::draw(float x, float y)
{
	settings.draw(x, y);
}