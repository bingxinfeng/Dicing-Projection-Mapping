#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D_inSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    //my code here
    float w,h,t;
    
    ofImage dice;
    void imageIn();
    void imageInSetup();
    void imageInUpdate();
    void imageOut();
    void imageOutSetup();
    void imageOutUpdate();
    float tileNum, spacing, deg, a, y, tIn, tOut;
    float alpha;
    
    void callFileName(string _fileName);
    string fname;
};
