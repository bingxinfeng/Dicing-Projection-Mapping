#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D4_source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    //---------------------------------
    void floatingsUnitSetup();
    void floatingsUnitUpdate();
    void floatingsUnit();
    
    int numOfPoints;
    float radius;
    float angleStep;
    float amt; //the noise size, i.e how random it is
    vector <float> noiseSeeds;
    float degT;
    
    //---------------------------------
    void bouncingBallSetup();
    void bouncingBallUpdate();
    void bouncingBallDraw();
    
    ofPoint bb;
    ofPoint sp;
    float bbRad;
    
    //---------------------------------
    void brightnessCheck();
    float white;
    float black;
    
    //---------------------------------
    float locX, locY, r;
    float w, h;
    float t;
    
    //---------------------------------
    void timer(float n);
    float n;
    float startTime;
    //---------------------------------
    ofImage dice;
    void imageOutSetup();
    void imageOutUpdate();
    void imageOut();
    float tileNum, spacing, deg, a, y, tOut;
    float clearColor;
    
    void sceneExit();
    float radExit;
};
