#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D6_source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    float t;
    float w,h;
    
    void floatingUnitSetup();
    void floatingUnitUpdate();
    void floatingUnit();
    vector <float> noiseSeeds;
    vector <ofPoint> pointLocation;
    int numOfPoints;
    float radius;
    float angleStep;
    float amt; //the noise size, i.e how random it is
    float amtT;
    
    void threeVerticalCirclesSetup();
    void threeVerticalCirclesUpdate();
    void threeVerticalCircles();
    float mt1, mt2, mt3;
    
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
