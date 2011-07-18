/*
 *  ColorsOfMovement.h
 *  ColorsOfMovement
 *
 *  Created by Paulo Barcelos on 10/5/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */


#include "ColorsOfMovement.h"

///////////////////////////////////////////////////////////////////////////////////
// Constructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ColorsOfMovement::ColorsOfMovement()
{	
}
///////////////////////////////////////////////////////////////////////////////////
// Destructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ColorsOfMovement::~ColorsOfMovement()
{	
}
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setup(int width, int height)
{	
	this->width = width;
	this->height = height;
	
	flushStoredFrames();
	
	loadSettings();
}
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::update(unsigned char * pixels)
{	
	ofImage * currentFrame = new ofImage();
	(*currentFrame).setFromPixels(pixels, width,  height, OF_IMAGE_COLOR);
	
	imgs.push_back(currentFrame);
	if (imgs.size() > numStoredFrames){
		delete imgs[0];
		imgs.erase(imgs.begin());
	}
	
	if (imgs.size() == numStoredFrames)
	{
		texR = (*imgs[0]).getTextureReference();
		texG = (*imgs[numStoredFrames / 2]).getTextureReference();
		texB = (*imgs[numStoredFrames - 1]).getTextureReference();
	}
	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::draw(float x, float y, float w, float h)
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	
	glBlendColor(255,0,0,255);
	glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
	ofDrawImageInRect(&texR, ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	
	glBlendColor(0,255,0,255);
	glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
	ofDrawImageInRect(&texG, ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	
	glBlendColor(0,0,255,255);
	glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
	ofDrawImageInRect(&texB, ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	
	glDisable(GL_BLEND);
}

void ColorsOfMovement::draw(float x, float y)
{
	draw(x, y, width, height);
}

///////////////////////////////////////////////////////////////////////////////////
// isReady ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool ColorsOfMovement::isReady()
{
	return (imgs.size() >= numStoredFrames) ? true : false;
}
///////////////////////////////////////////////////////////////////////////////////
// setStoredFrames ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setStoredFrames(int numFrames){
	if(numFrames < 3) numFrames = 3;
	numStoredFrames = numFrames;
	settings.setValue("STORED_FRAMES", numStoredFrames, 0);
	saveSettings();				  
	
	flushStoredFrames();
}
///////////////////////////////////////////////////////////////////////////////////
// getStoreFrames -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int ColorsOfMovement::getStoredFrames(){
	return numStoredFrames;
}
///////////////////////////////////////////////////////////////////////////////////
// flushStoredFrames --------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::flushStoredFrames(){
	while (imgs.size() > 0){
		delete imgs[0];
		imgs.erase(imgs.begin());
	}
}
///////////////////////////////////////////////////////////////////////////////////
// getWidth() ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int ColorsOfMovement::getWidth()
{
	return width;
}
///////////////////////////////////////////////////////////////////////////////////
// getHeight() --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int ColorsOfMovement::getHeight()
{
	return height;
}
///////////////////////////////////////////////////////////////////////////////////
// saveSettings -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::saveSettings(){
	settings.saveFile("ColorsOfMovement.xml");
}

///////////////////////////////////////////////////////////////////////////////////
// loadSettings ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::loadSettings(){
	settings.loadFile("ColorsOfMovement.xml");
	//if the settings  doesn't exist we assigns the default
	setStoredFrames(settings.getValue("STORED_FRAMES", CM_DEFAULT_NUM_STORED_FRAMES));
}
