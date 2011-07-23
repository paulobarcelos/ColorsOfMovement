/*
 *  ColorsOfMovement.h
 *  ColorsOfMovement
 *
 *  Created by Paulo Barcelos on 10/5/10.
 *  Copyright 2010 Paulo Barcelos. All rights reserved.
 *
 */

#ifndef _COLORS_OF_MOVEMENT
#define _COLORS_OF_MOVEMENT

#define CM_DEFAULT_NUM_STORED_FRAMES 30

#include "ofMain.h"
#include "ofxKeyboardSettings.h"
#include "ofxDrawingUtils.h"

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ColorsOfMovement {
	
public:
	
	ColorsOfMovement();
	~ColorsOfMovement();
	
	void				setup(int width, int height);
	void				update(unsigned char * pixels);
	void				keyPressed(int key);
	void				draw(float x, float y, float w, float h);
	void				draw(float x, float y);
	
	bool				isReady();
	void				setStoredFrames(int numFrames);
	int					getStoredFrames();	
	
	int					getWidth();
	int					getHeight();
	
	ofTexture &			getTextureReference();

private:
	
	vector <ofImage *>	imgs;
	
	int					width, height;
	ofTexture			texR, texG, texB;
	
	void				drawFBO();
	ofFbo				fbo;
	
	ofxKeyboardSettings	settings;
	
	ofxKeyboardIntProperty* numStoredFramesProperty;
	int					numStoredFrames;
	
	void				flushStoredFrames();
		
};
#endif