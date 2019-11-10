#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D3_source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    float w,h;
    
    void sinWave();
    float width, length, length2, rad, t;
    
    void zoomCircles();
    void groupDots();
    void groupDotsSetup();
    void groupDotsUpdate();
    vector <float> noiseSeeds;
    float dotNum;
    
    void sceneExit();
    float radExit;
    
    void timer(float n);
    float n;
    float startTime;
    
    ofImage dice;
    void imageOutSetup();
    void imageOutUpdate();
    void imageOut();
    float tileNum, spacing, deg, a, y, tOut;
    float clearColor;
};
