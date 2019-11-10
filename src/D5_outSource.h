#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D5_outSource : public ofx::piMapper::FboSource {
public:
    void setup();
    void update();
    void draw();
    void reset();
    void setName(string _name);
    float time;
    
    //my code here
    ofImage dice;
    void imageOut();
    void imageOutSetup();
    void imageOutUpdate();
    float tileNum, spacing, deg, a, y, tOut;
    float exitSp;
    
    float w,h,t;
    
};
