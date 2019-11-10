#pragma once

#include "ofMain.h"
#include "FboSource.h"

class D_stillSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void reset();
        void setName(string _name);
        float time;
    
    //my code here
    float w,h;
    
    ofImage dice;
    
    void callFileName(string _fileName);
    string fname;
};
