#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D1_03noImgSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    float locX,locY,r;
    float w,h;
    float brightness;
    float t;
    
    void boucingCenterCircle();
    void boucingCenterCircleSetup();
    void boucingCenterCircleUpdate();
    float tCenter;
    
    void centerWave();
    void centerWaveSetup();
    void centerWaveUpdate();
    float tScale;
    float noiseSeed;
    
    ofImage dice;
    void imageOut();
    void imageOutSetup();
    void imageOutUpdate();
    float tileNum, spacing, deg, a, y, tOut;
    float underDotColor;
    
    void sceneExit();
    float radExit;
};
