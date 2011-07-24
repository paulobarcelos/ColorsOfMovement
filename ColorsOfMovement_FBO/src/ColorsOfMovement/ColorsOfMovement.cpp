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

	ofFbo::Settings s;
	s.width				= width;
	s.height			= height;
	s.numColorbuffers	= 1;
	s.numSamples		= 0;
	fbo.allocate(s);
	
	settings.setup('c', "Colors_of_Movement");
	numStoredFramesProperty = settings.addProperty(&numStoredFrames, "Stored_Frames", 3, 300, 1, CM_DEFAULT_NUM_STORED_FRAMES);

	flushStoredFrames();
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
// keyPressed ---------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::keyPressed(int key){
	settings.proccessKey(key);
}
///////////////////////////////////////////////////////////////////////////////////
// draw ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::draw(float x, float y, float w, float h)
{
	drawFBO();
	ofDrawImageInRect(&(fbo.getTextureReference()), ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	//settings.draw();
}

void ColorsOfMovement::draw(float x, float y)
{
	draw(x, y, width, height);
}
///////////////////////////////////////////////////////////////////////////////////
// drawFBO ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::drawFBO()
{
	fbo.begin();
		// "clear" the fbo by drawing a black rectangle over it
		ofSetColor(0);
		ofRect(0, 0, width, height);
		ofSetColor(255);
		
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
	//settings.setProperty(numStoredFramesProperty, numFrames);
	 
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
