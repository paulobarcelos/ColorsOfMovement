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
void ColorsOfMovement::setup(int width, int height, int numStoredFrames, int mode)
{	
	this->width = width;
	this->height = height;
	
	setMode(mode);
	setNumStoredFrames(numStoredFrames);
}
///////////////////////////////////////////////////////////////////////////////////
// setMode ------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setMode(int mode)
{
	this->mode = mode;
	switch (mode) {
		case CM_FBO_MODE:
			fbo.allocate(width, height);
			break;
		case CM_PIXEL_MATH_MODE:
			totalPixels = width * height * 3;
			if(RGBData != NULL) delete RGBData;
			RGBData = new unsigned char[totalPixels];
			tex.clear();
			tex.allocate(width, height, GL_RGB);
			break;
	}
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
		if (mode == CM_PIXEL_MATH_MODE){
			unsigned char* pixelsR, * pixelsG, * pixelsB;
			pixelsB =  (*imgs[0]).getPixels();
			pixelsG =  (*imgs[numStoredFrames / 2]).getPixels();
			pixelsR =  (*imgs[numStoredFrames - 1]).getPixels();
			
			
			int channel, r, g, b;
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
		else if (mode == CM_GL_BLEND_MODE || mode == CM_FBO_MODE){
			texR = (*imgs[0]).getTextureReference();
			texG = (*imgs[numStoredFrames / 2]).getTextureReference();
			texB = (*imgs[numStoredFrames - 1]).getTextureReference();
		}
	}	
}

///////////////////////////////////////////////////////////////////////////////////
// draw ---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::draw(float x, float y, float w, float h)
{
	if (mode == CM_PIXEL_MATH_MODE){
		ofDrawImageInRect(&tex, ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	}
	else if(mode == CM_GL_BLEND_MODE){		
		ofSetColor(0);
		ofRect(x, y, w, h);
		ofSetColor(255);
		
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
	else if(mode == CM_FBO_MODE){
		drawFBO();
		ofDrawImageInRect(&(fbo.getTextureReference()), ofRectangle(x, y, w, h), false, true, VERTICAL_CENTER, HORIZONTAL_CENTER);
	}

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
// setStoredFrames ----------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
void ColorsOfMovement::setNumStoredFrames(int numStoredFrames){
	if(numStoredFrames < 3) numStoredFrames = 3;
	this->numStoredFrames = numStoredFrames;
	flushStoredFrames();
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
// getTextureReference() ----------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////
ofTexture & ColorsOfMovement::getTextureReference()
{
	switch (mode) {
		case CM_FBO_MODE:
			return fbo.getTextureReference();
			break;
		case CM_PIXEL_MATH_MODE:
			return tex;
			break;
		case CM_GL_BLEND_MODE:
			return tex; // this texture will be unitialized
			break;
	}
}
