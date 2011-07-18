/*
 *  ofDrawImageInRect.h
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 10/5/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

enum verticalAlignment{
	VERTICAL_CENTER = 0,
	VERTICAL_TOP,
	VERTICAL_BOTTOM
};

enum horizontalAlignment{
	HORIZONTAL_CENTER = 10,
	HORIZONTAL_LEFT,
	HORIZONTAL_RIGHT
};


void swapf(float*a, float*b);

ofRectangle ofDrawImageInRect( ofTexture* i, 
						ofRectangle myRect, 
						bool rotate90, 
						bool flipHorizontal,
						verticalAlignment val = VERTICAL_BOTTOM, 
						horizontalAlignment hal = HORIZONTAL_CENTER 
					   );


ofRectangle ofCalcRectForDrawImageInRect(	ofTexture * i, 
											ofRectangle myRect, 
											bool rotate90, 
											bool flipHorizontal, 
											verticalAlignment val, 
											horizontalAlignment hal 
										 );