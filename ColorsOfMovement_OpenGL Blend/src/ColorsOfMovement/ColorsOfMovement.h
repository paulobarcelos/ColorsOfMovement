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
#include "ofxXmlSettings.h"
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
	void				draw(float x, float y, float w, float h);
	void				draw(float x, float y);
	
	bool				isReady();
	void				setStoredFrames(int numFrames);
	int					getStoredFrames();
	
	void				saveSettings();
	void				loadSettings();
	
	int					getWidth();
	int					getHeight();
	
private:
	
	int					totalPixels;	
	unsigned char		* RGBData;
	unsigned char		* pixelsR, * pixelsG, * pixelsB;	
	int					channel, r, g, b;
	
	int					MAX_STORED_FRAMES;
	
	vector <ofImage *>	imgs;
	
	int					width, height;
	ofTexture			texR, texG, texB;
	
	ofxXmlSettings		settings;
	int					numStoredFrames;
	
	void				flushStoredFrames();
	
};
#endif