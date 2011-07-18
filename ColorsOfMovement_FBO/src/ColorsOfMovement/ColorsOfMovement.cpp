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
	
	ofFbo::Settings s;
	s.width				= width;
	s.height			= height;
	s.numColorbuffers	= 1;
	s.numSamples		= 0;
	fbo.allocate(s);
	
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
		
		texR = (*imgs[0]).getTextureReference();
		texG = (*imgs[MAX_STORED_FRAMES / 2]).getTextureReference();
		texB = (*imgs[MAX_STORED_FRAMES - 1]).getTextureReference();
	}
	
}
///////////////////////////////////////////////////////////////////////////////////
// draw ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::draw(float x, float y, float w, float h)
{
	fbo.draw(x, y, w, h);
}

void ColorsOfMovement::draw(float x, float y)
{
	fbo.draw(x, y);
}
///////////////////////////////////////////////////////////////////////////////////
// drawFBO ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::drawFBO()
{
	fbo.begin();
		// "clear" the fbo by drawing a black rectangle over it
		ofSetColor(0, 0, 0);
		ofRect(0, 0, width, height);
		ofSetColor(255, 255, 255);
		
		// and draw each of the textures, with their coresponden't blengin mode
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
	
		glBlendColor(255,0,0,255);
		glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
		texR.draw(0, 0);
	
		glBlendColor(0,255,0,255);
		glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
		texG.draw(0, 0);
	
		glBlendColor(0,0,255,255);
		glBlendFunc(GL_CONSTANT_COLOR, GL_ONE);
		texB.draw(0, 0);
	
		glDisable(GL_BLEND);
	fbo.end();
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
// getStoreFrames -----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
int ColorsOfMovement::getStoredFrames(){
	 return MAX_STORED_FRAMES;
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
	return fbo.getTextureReference();
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
