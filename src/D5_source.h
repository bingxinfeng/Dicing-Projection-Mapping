#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D5_source : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    void floatingUnitSetup();
    void floatingUnitUpdate();
    void floatingUnit(float alpha);
    int numOfPoints;
    float radius;
    float angleStep;
    float amt; //the noise size, i.e how random it is
    vector <float> noiseSeeds;
    
    void boucingCenter();
    void cornerPoint();
    
    float w, h;
    float t;
    
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
