#include "D3_outSource.h"

void D3_outSource::setup(){
    // Give our source a decent name
    name = "D3_out Source";
    // Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    //ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    dice.load("dice3.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D3_outSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void D3_outSource::setName(string _name){
    name = _name;
}

//--------------------------------------------------------------
// Don't do any drawing here
void D3_outSource::update(){
    imageOutUpdate();
    
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D3_outSource::draw(){
    ofClear(0);//clear the buffer
    //Clears the color and depth bits of current renderer and replaces it with an ofColor
    
    imageOut();
    
}
//==============================================================
void D3_outSource::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 280; //move from 280
}
//--------------------------------------------------------------
void D3_outSource::imageOutUpdate(){
    tOut+=0.5;
    if(tOut>=400){
        tOut=400;
    }
    if(tOut>=370){
        exitSp +=4;
    }
    if(w/8-exitSp<=0){
        exitSp=w/8;
    }
}
//--------------------------------------------------------------
void D3_outSource::imageOut(){
    //centerDot under the image layer
    ofSetColor(255);
    ofDrawCircle(w/4, h/4, w/8-exitSp);
    ofDrawCircle(w/4*3, h/4*3, w/8-exitSp);
    ofDrawCircle(w/2, h/2, w/8-exitSp);
    
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i+t;
        a = sin(ofDegToRad(90/tileNum*i+tOut))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tOut<<endl;
    }
}
