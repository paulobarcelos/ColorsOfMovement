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
	loadSettings();
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

	ofFbo::Settings s;
	s.width				= width;
	s.height			= height;
	s.numColorbuffers	= 1;
	s.numSamples		= 0;
	fbo.allocate(s);

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
	drawFBO();
	ofDrawImageInRect(&(fbo.getTextureReference()), ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
}

void ColorsOfMovement::draw(float x, float y)
{
	fbo.draw(x, y, width, height);
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
	return fbo.getTextureReference();
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
