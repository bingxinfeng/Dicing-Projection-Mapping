#include "D6_outSource.h"

void D6_outSource::setup(){
    // Give our source a decent name
    name = "D6_out Source";
    // Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    //ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    dice.load("dice6.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D6_outSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}

//--------------------------------------------------------------
void D6_outSource::setName(string _name){
    name = _name;
}

//--------------------------------------------------------------
// Don't do any drawing here
void D6_outSource::update(){
    imageOutUpdate();
    
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D6_outSource::draw(){
    ofClear(0);//clear the buffer
    //Clears the color and depth bits of current renderer and replaces it with an ofColor
    
    imageOut();
    
}
//==============================================================
void D6_outSource::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 280; //move from 280
}
//--------------------------------------------------------------
void D6_outSource::imageOutUpdate(){
    tOut+=0.5;
    if(tOut>=400){
        tOut=400;
    }
}
//--------------------------------------------------------------
void D6_outSource::imageOut(){
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i+t;
        a = sin(ofDegToRad(90/tileNum*i+tOut))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tOut<<endl;
    }
}
