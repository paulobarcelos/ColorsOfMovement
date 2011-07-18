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
	RGBData = NULL;
}
///////////////////////////////////////////////////////////////////////////////////
// Destructor --------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ColorsOfMovement::~ColorsOfMovement()
{	
	if(RGBData != NULL) delete RGBData;
}
///////////////////////////////////////////////////////////////////////////////////
// setup --------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setup(int width, int height)
{	
	this->width = width;
	this->height = height;
	
	totalPixels = width * height * 3;
	if(RGBData != NULL) delete RGBData;
	RGBData = new unsigned char[totalPixels];
	tex.clear();
	tex.allocate(width, height, GL_RGB);
	
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
		pixelsB =  (*imgs[0]).getPixels();
		pixelsG =  (*imgs[numStoredFrames / 2]).getPixels();
		pixelsR =  (*imgs[numStoredFrames - 1]).getPixels();
		
		
		channel = 0;
		for (int i = 0; i < totalPixels ; i++){
			if ( channel == 0 ) // R
			{
				r = pixelsR[i];
				channel ++;
			}
			else if ( channel == 1 ) // G
			{
				g = pixelsG[i];
				channel ++;
			}	
			else if ( channel == 2 ) // B
			{
				b =  pixelsB[i];
				
				RGBData[i-2] = r;
				RGBData[i-1] = g;
				RGBData[i] = b;
				channel = 0;
			}
			
		}
		tex.loadData(RGBData, width, height, GL_RGB);
	}
	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::draw(float x, float y, float w, float h)
{
	ofDrawImageInRect(&tex, ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
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
// getTextureReference() ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ofTexture & ColorsOfMovement::getTextureReference()
{
	return tex;
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
