#include "D2_source.h"

void D2_source::setup(){
	// Give our source a decent name
    name = "D2_ Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    r = 5;
    t = 0;
    degT = 0;
    
    movingBackForthSetup();
    
    dice.load("dice2.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D2_source::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}
//--------------------------------------------------------------
void D2_source::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
// Don't do any drawing here
void D2_source::update(){
    

    //run the animation after image out
    if(tOut>=400){
        t+=0.15;
        degT+=0.05;
    }
    
    movingBackForthUpdate();
    imageOutUpdate();
    
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D2_source::draw(){
    //ofClear(0);//clear the buffer
    
    ofSetColor(0,0,0,1);
    ofFill();
    //ofDrawRectangle(0, 0, w, h);
    
    spiralCircle();
    //mirror it
    ofPushMatrix();
    ofTranslate(w, h);
    ofRotateYDeg(180);
    ofRotateXDeg(180);
    spiralCircle();
    ofPopMatrix();
    
    movingBackForth();
    
    if(t>190){ //main animation last about 17s
        sceneExit();
    }
    
    imageOut();
    
    cout<<t<<endl;
    
}


//==============================================================
void D2_source::spiralCircle(){
    
    ofPushMatrix();
    ofTranslate(w/2,h/2);
    
    //when the circles get very close to the 'dice2 location', stop(attract) them there. a&b are the distance between the circle and the 'dice2 location'
    float a =abs(locX-w/4);
    if(a<3){
        locX = w/4;
        r=50;
    }
    float b =abs(locY-h/4);
    if(b<3){
        locY = h/4;
        r=50;
    }
    
    //when the circle is still far away from 'dice2Location', run as they are
    if(a>=3||b>=3){
        
        //degT control the rotate speed, t control the rotate (location) range
        locX = cos(degT);
        locY = sin(degT);
        //calculate the edge locations, i.e. the diam
        locX = ofMap(locX,-1,1,0,0+t); //x->cos->(-1,1,xLeft,xRight)
        locY = ofMap(locY,-1,1,0+t,0); //y->sin->(-1,1,yDown,yUp);
        
        r = r+t*0.0001;
        if(r>=50){
            r=50;
        }
    }
    
    ofSetColor(255);
    ofNoFill();
    ofDrawCircle(locX,locY,r);
    
    ofPopMatrix();
}

//==============================================================
void D2_source::movingBackForthSetup(){
    xs=w/4;
    ys=h/4;
    x1=w/4;
    y1=h/4;
    x2=w-xs;
    y2=h-xs;
    mt = 2;
}
//--------------------------------------------------------------
void D2_source::movingBackForthUpdate(){
    //moving back and forth
    x1 = x1 + mt;
    y1 = y1 + mt;
    if(x1==x2 && y1==y2){
        mt = -mt;
    }
    if(x1==xs && y1==ys){
        mt = -mt;
        x1 = x1 + mt;
        y1 = y1 + mt;
    }
}
//--------------------------------------------------------------
void D2_source::movingBackForth(){
    float a = abs(x1-w/2);
    float s = ofMap(a,0,w/4,0,1);
    ofSetColor(255-255*s);
    ofFill();
    ofDrawCircle(x1,y1,r*s);
}

//==============================================================
void D2_source::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    clearColor = 255;
}
//--------------------------------------------------------------
void D2_source::imageOutUpdate(){
    tOut+=0.5;
    
    if(tOut>=400){
        tOut=400;
        clearColor = 0;
    }
}
//--------------------------------------------------------------
void D2_source::imageOut(){
    ofSetColor(0,0,0,clearColor);
    ofDrawRectangle(0, 0, w, h);
    
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i+t;
        a = sin(ofDegToRad(90/tileNum*i+tOut))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tOut<<endl;
    }
}

//==============================================================
void D2_source::sceneExit(){
    radExit+=7;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}
