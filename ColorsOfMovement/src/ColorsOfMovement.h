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

#include "ofMain.h"
#include "ofxDrawingUtils.h"

////////////////////////////////////////////////////////////
// CONSTANTS -----------------------------------------------
////////////////////////////////////////////////////////////
enum ColorsOfMovementModes {
	CM_PIXEL_MATH_MODE = 0,
	CM_GL_BLEND_MODE,
	CM_FBO_MODE
};
#define CM_MIN_NUM_STORED_FRAMES 3
#define CM_MAX_NUM_STORED_FRAMES 300
#define CM_STEP_NUM_STORED_FRAMES 1
#define CM_DEFAULT_NUM_STORED_FRAMES 30

#define CM_DEFAULT_MODE CM_GL_BLEND_MODE

////////////////////////////////////////////////////////////
// CLASS DEFINITION ----------------------------------------
////////////////////////////////////////////////////////////
class ColorsOfMovement {
	
public:
	
	ColorsOfMovement();
	~ColorsOfMovement();
	
	void				setup(int width, int height, int numStoredFrames = CM_DEFAULT_NUM_STORED_FRAMES, int mode = CM_DEFAULT_MODE);
	void				update(unsigned char * pixels);
	
	void				draw(float x, float y, float w, float h);
	void				draw(float x, float y);
	
	void				setMode(int mode);
	int					getMode(){return mode;};
	int					getModeMin(){return CM_PIXEL_MATH_MODE;};
	int					getModeMax(){return CM_FBO_MODE;};
	int					getModeStep(){return 1;};
	
	void				setNumStoredFrames(int numStoredFrames);
	int					getNumStoredFrames(){return numStoredFrames;};
	int					getNumStoredFramesMin(){return CM_MIN_NUM_STORED_FRAMES;};
	int					getNumStoredFramesMax(){return CM_MAX_NUM_STORED_FRAMES;};
	int					getNumStoredFramesStep(){return CM_STEP_NUM_STORED_FRAMES;};
	
	bool				isReady(){return (imgs.size() >= numStoredFrames);};
	
	int					getWidth(){return width;};
	int					getHeight(){return height;};
	
	ofTexture &			getTextureReference();

private:
	int					mode;
	vector <ofImage *>	imgs;	
	int					width, height;
	int					numStoredFrames;
	
	void				flushStoredFrames();
	
	// used only by CM_PIXEL_MATH_MODE
	int					totalPixels;	
	unsigned char		* RGBData;
	ofTexture			tex;
	
	// used only by CM_FBO_MODE
	void				drawFBO();
	ofFbo				fbo;
	
	// used only by CM_FBO_MODE && CM_GL_BLEND_MODE
	ofTexture			texR, texG, texB;;
	
	
	
	
			
};
#endif