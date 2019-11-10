#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "BouncingBallsSource.h"
#include "MovingRectSource.h"

#include "D_inSource.h"
#include "D_stillSource.h"
#include "D1_outSource.h"
#include "D2_outSource.h"
#include "D3_outSource.h"
#include "D4_outSource.h"
#include "D5_outSource.h"
#include "D6_outSource.h"

#include "D1_03noImgSource.h"
#include "D2_source.h"
#include "D3_source.h"
#include "D4_source.h"
#include "D5_source.h"
#include "D6_source.h"

#include "VideoSource.h"
#include "SceneManager.h"


class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;

		// By using a custom source that is derived from FboSource
		// you will be able to see the source listed in sources editor
        BouncingBallsSource * bouncingBallsSource;
        MovingRectSource * movingRectSource;
    
    D_inSource * d_inSource;
    D_inSource * d_inSource2;
    D_inSource * d_inSource3;
    D_inSource * d_inSource4;
    D_inSource * d_inSource5;
    D_inSource * d_inSource6;
    
    D_stillSource * d_stillSource;
    D_stillSource * d_stillSource2;
    D_stillSource * d_stillSource3;
    D_stillSource * d_stillSource4;
    D_stillSource * d_stillSource5;
    D_stillSource * d_stillSource6;
    
    D1_outSource * d1_outSource;
    D2_outSource * d2_outSource;
    D3_outSource * d3_outSource;
    D4_outSource * d4_outSource;
    D5_outSource * d5_outSource;
    D6_outSource * d6_outSource;
    
    D1_03noImgSource * d1_03noImgSource;
    D2_source * d2_source;
    D3_source * d3_source1;
    D3_source * d3_source2;
    D3_source * d3_source3;
    D4_source * d4_source;
    D5_source * d5_source;
    D5_source * d5_source2;
    D6_source * d6_source;
    
        ofImage dummyObjects;
        SceneManager sceneManager;
};
