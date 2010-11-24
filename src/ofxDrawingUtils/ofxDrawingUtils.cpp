/*
 *  ofDrawImageInRect.cpp
 *  emptyExample
 *
 *  Created by Oriol Ferrer Mesià on 10/5/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#include "ofxDrawingUtils.h"

void swapf(float*a, float*b){
	float t = *a;
	*a = *b;
	*b = t;
}

ofRectangle ofCalcRectForDrawImageInRect( ofTexture * i, ofRectangle myRect, bool rotate90, bool flipHorizontal, verticalAlignment val, horizontalAlignment hal ){

	if (i==NULL){ 
		printf("ofCalcRectForDrawImageInRect: cant draw NULL pointer ofTexture\n"); 
		return ofRectangle();
	}
	
	
	ofRectangle r;
	float tx0 , tx1, ty0, ty1;
	
	if (rotate90 == false){

		float tw = i->getWidth();
		float th = i->getHeight();

		float aspectRatio =  (float) tw / (float) th;			// >1 means landscape
		float rectAspect = myRect.width / myRect.height;
		
		float xscale = myRect.width / tw;						// if > 1 we need to stretch		
		float yscale = myRect.height / th;
				
		if ( xscale < yscale ){		//	we fit to y

			ty0 = 0;
			ty1 = th;
			
			if (flipHorizontal){	//
				if (hal==HORIZONTAL_LEFT) hal = HORIZONTAL_RIGHT;
				else
					if (hal==HORIZONTAL_RIGHT) hal = HORIZONTAL_LEFT;
			}
			switch (hal) {
				case HORIZONTAL_CENTER: 
					tx0 = tw/2. - (th/2.) * rectAspect;
					tx1 = tw/2. + (th/2.) * rectAspect;
					break;
				case HORIZONTAL_LEFT:
					tx0 = 0;
					tx1 = (th) * rectAspect;
					break;					
				case HORIZONTAL_RIGHT: 
					tx0 = tw - (th) * rectAspect;
					tx1 = tw;
					break;
			}
			
		}else{

			tx0 = 0;
			tx1 = tw;
			
			switch (val) {
				case VERTICAL_CENTER: 
					ty0 = th/2. - (tw/2.) * (1./rectAspect);
					ty1 = th/2. + (tw/2.) * (1./rectAspect);
					break;
				case VERTICAL_BOTTOM: 
					ty0 = th - (tw) * (1./rectAspect);
					ty1 = th;
					break;
				case VERTICAL_TOP:
					ty0 = 0;
					ty1 = (tw) * (1./rectAspect);

					break;
			}
		}

		if (flipHorizontal)
			swapf(&tx0, &tx1);
		
		r.x = MIN(tx0, tx1);
		r.y = ty0;
		r.width = fabs(tx1 - tx0);
		r.height = fabs(ty1 - ty0);

	}else{														//need to rotate 90
		
		float tw = i->getHeight();
		float th = i->getWidth();
		
		float rectAspect = myRect.width / myRect.height;
		rectAspect = 1./rectAspect;
		
		float yscale = myRect.width / tw;						// if > 1 we need to stretch		
		float xscale = myRect.height / th;
		
		if ( xscale < yscale ){		//	we fit to y
			
			ty0 = 0;
			ty1 = tw;
			
			switch (val) {
				case VERTICAL_CENTER: 
					tx0 = th/2. - (tw/2.) * rectAspect;
					tx1 = th/2. + (tw/2.) * rectAspect;
					break;
				case VERTICAL_TOP:
					tx0 = th - (tw) * rectAspect;
					tx1 = th;
					break;					
				case VERTICAL_BOTTOM: 
					tx0 = 0;
					tx1 = (tw) * rectAspect;
					break;
			}
					
		}else{

			tx0 = 0;
			tx1 = th;			

			if (flipHorizontal){	//
				if (hal==HORIZONTAL_LEFT) hal = HORIZONTAL_RIGHT;
				else
					if (hal==HORIZONTAL_RIGHT) hal = HORIZONTAL_LEFT;
			}
			switch (hal) {
				case HORIZONTAL_CENTER: 
					ty1 = tw/2. + (th/2.) * (1./rectAspect);
					ty0 = tw/2. - (th/2.) * (1./rectAspect);
					break;
				case HORIZONTAL_LEFT:
					ty1 = (th) * (1./rectAspect);
					ty0 = 0;
					break;					
				case HORIZONTAL_RIGHT: 
					ty1 = tw;
					ty0 = tw - th * (1./rectAspect);
					break;
			}

		}

		r.x = ty0;
		r.y = tx0;
		r.width = ty1 - ty0;
		r.height = tx1 - tx0;

		if (flipHorizontal)
			swapf(&ty0, &ty1);

	}

	return r;
}

ofRectangle ofDrawImageInRect( ofTexture * i, ofRectangle myRect, bool rotate90, bool flipHorizontal, verticalAlignment val, horizontalAlignment hal ){

	if (i==NULL){ 
		printf("ofDrawImageInRect: cant draw NULL pointer ofTexture\n"); 
		return ofRectangle();
	}
	
	//glColor3f(1,1,1);
	
	ofRectangle r;
	float tx0 , tx1, ty0, ty1;
	
	i->bind();

	if (rotate90 == false){

		float tw = i->getWidth();
		float th = i->getHeight();

		float aspectRatio =  (float) tw / (float) th;			// >1 means landscape
		float rectAspect = myRect.width / myRect.height;
		
		float xscale = myRect.width / tw;						// if > 1 we need to stretch		
		float yscale = myRect.height / th;
				
		if ( xscale < yscale ){		//	we fit to y

			ty0 = 0;
			ty1 = th;
			
			if (flipHorizontal){	//
				if (hal==HORIZONTAL_LEFT) hal = HORIZONTAL_RIGHT;
				else
					if (hal==HORIZONTAL_RIGHT) hal = HORIZONTAL_LEFT;
			}
			switch (hal) {
				case HORIZONTAL_CENTER: 
					tx0 = tw/2. - (th/2.) * rectAspect;
					tx1 = tw/2. + (th/2.) * rectAspect;
					break;
				case HORIZONTAL_LEFT:
					tx0 = 0;
					tx1 = (th) * rectAspect;
					break;					
				case HORIZONTAL_RIGHT: 
					tx0 = tw - (th) * rectAspect;
					tx1 = tw;
					break;
			}
			
		}else{

			tx0 = 0;
			tx1 = tw;
			
			switch (val) {
				case VERTICAL_CENTER: 
					ty0 = th/2. - (tw/2.) * (1./rectAspect);
					ty1 = th/2. + (tw/2.) * (1./rectAspect);
					break;
				case VERTICAL_BOTTOM: 
					ty0 = th - (tw) * (1./rectAspect);
					ty1 = th;
					break;
				case VERTICAL_TOP:
					ty0 = 0;
					ty1 = (tw) * (1./rectAspect);

					break;
			}
		}

		if (flipHorizontal)
			swapf(&tx0, &tx1);

		glBegin(GL_QUADS);
			glTexCoord2f( tx0, ty0 );
			glVertex2f( myRect.x, myRect.y );
			glTexCoord2f( tx0, ty1 );
			glVertex2f( myRect.x, myRect.y + myRect.height );
			glTexCoord2f( tx1, ty1 );
			glVertex2f( myRect.x + myRect.width, myRect.y + myRect.height );
			glTexCoord2f( tx1, ty0 );
			glVertex2f( myRect.x + myRect.width, myRect.y );
		glEnd();
		
		r.x = tx0;
		r.y = ty0;
		r.width = tx1 - tx0;
		r.height = ty1 - ty0;

	}else{														//need to rotate 90
		
		float tw = i->getHeight();
		float th = i->getWidth();
		
		float rectAspect = myRect.width / myRect.height;
		rectAspect = 1./rectAspect;
		
		float yscale = myRect.width / tw;						// if > 1 we need to stretch		
		float xscale = myRect.height / th;
		
		if ( xscale < yscale ){		//	we fit to y
			
			ty0 = 0;
			ty1 = tw;
			
			switch (val) {
				case VERTICAL_CENTER: 
					tx0 = th/2. - (tw/2.) * rectAspect;
					tx1 = th/2. + (tw/2.) * rectAspect;
					break;
				case VERTICAL_TOP:
					tx0 = th - (tw) * rectAspect;
					tx1 = th;
					break;					
				case VERTICAL_BOTTOM: 
					tx0 = 0;
					tx1 = (tw) * rectAspect;
					break;
			}
					
		}else{

			tx0 = 0;
			tx1 = th;			

			if (flipHorizontal){	//
				if (hal==HORIZONTAL_LEFT) hal = HORIZONTAL_RIGHT;
				else
					if (hal==HORIZONTAL_RIGHT) hal = HORIZONTAL_LEFT;
			}
			switch (hal) {
				case HORIZONTAL_CENTER: 
					ty1 = tw/2. + (th/2.) * (1./rectAspect);
					ty0 = tw/2. - (th/2.) * (1./rectAspect);
					break;
				case HORIZONTAL_LEFT:
					ty1 = (th) * (1./rectAspect);
					ty0 = 0;
					break;					
				case HORIZONTAL_RIGHT: 
					ty1 = tw;
					ty0 = tw - th * (1./rectAspect);
					break;
			}

		}

		r.x = ty0;
		r.y = tx0;
		r.width = ty1 - ty0;
		r.height = tx1 - tx0;

		if (flipHorizontal)
			swapf(&ty0, &ty1);

		glBegin(GL_QUADS);
			glTexCoord2f( tx1, ty0 );
			glVertex2f( myRect.x, myRect.y );
			glTexCoord2f( tx0, ty0 );
			glVertex2f( myRect.x, myRect.y + myRect.height );
			glTexCoord2f( tx0, ty1 );			
			glVertex2f( myRect.x + myRect.width, myRect.y + myRect.height );
			glTexCoord2f( tx1, ty1 );
			glVertex2f( myRect.x + myRect.width, myRect.y );
		glEnd();	
		
	}
	
	i->unbind();

	return r;
}