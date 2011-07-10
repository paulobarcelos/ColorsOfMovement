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
	MAX_STORED_FRAMES = 30;
	loadSettings();
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
	
	// Clear the stored images
	while (imgs.size() > 0){
		delete imgs[0];
		imgs.erase(imgs.begin());
	}
		
}
///////////////////////////////////////////////////////////////////////////////////
// update -------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::update(unsigned char * pixels)
{	
	ofImage * currentFrame = new ofImage();
	(*currentFrame).setFromPixels(pixels, width,  height, OF_IMAGE_COLOR);
	
	imgs.push_back(currentFrame);
	if (imgs.size() > MAX_STORED_FRAMES){
		delete imgs[0];
		imgs.erase(imgs.begin());
	}
	
	if (imgs.size() == MAX_STORED_FRAMES)
	{
		pixelsB =  (*imgs[0]).getPixels();
		pixelsG =  (*imgs[MAX_STORED_FRAMES / 2]).getPixels();
		pixelsR =  (*imgs[MAX_STORED_FRAMES - 1]).getPixels();
		
		
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
	tex.draw(x, y, w, h);
}

void ColorsOfMovement::draw(float x, float y)
{
	tex.draw(x, y);
}
///////////////////////////////////////////////////////////////////////////////////
// isReady ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
bool ColorsOfMovement::isReady()
{
	return (imgs.size() >= MAX_STORED_FRAMES) ? true : false;
}
///////////////////////////////////////////////////////////////////////////////////
// setStoredFrames ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setStoredFrames(int numFrames){
	if(numFrames < 3) numFrames = 3;
	MAX_STORED_FRAMES = numFrames; 
	setup(width, height);
}
///////////////////////////////////////////////////////////////////////////////////
// getStoreFrames ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int ColorsOfMovement::getStoredFrames(){
	 return MAX_STORED_FRAMES;
}
///////////////////////////////////////////////////////////////////////////////////
// saveSettings -------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::saveSettings(){
	
	FILE * f = fopen( ofToDataPath("ColorsOfMovement_settings.txt", TRUE).c_str() ,"w");

	if ( f == nil )
		return;
	
	fprintf (f,"MAX_STORED_FRAMES %d\n",MAX_STORED_FRAMES);
	fclose(f);
}

///////////////////////////////////////////////////////////////////////////////////
// loadSettings ------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::loadSettings(){

	FILE * f = fopen( ofToDataPath("ColorsOfMovement_settings.txt", TRUE).c_str() ,"r");

	if (f==nil)
		return;
	
	fscanf (f,"MAX_STORED_FRAMES %d\n", &MAX_STORED_FRAMES );
	fclose(f);
}
