#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D2_source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    float w,h;
    
    void spiralCircle();
    float locX, locY, r;
    float t,degT;
    
    void movingBackForthSetup();
    void movingBackForthUpdate();
    void movingBackForth();
    float x1,y1,x2,y2,xs,ys;
    float mt;
    
    ofImage dice;
    void imageOutSetup();
    void imageOutUpdate();
    void imageOut();
    float tileNum, spacing, deg, a, y, tOut;
    float clearColor;
    
    void sceneExit();
    float radExit;
};
