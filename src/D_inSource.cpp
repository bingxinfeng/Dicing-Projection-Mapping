#include "D_inSource.h"

void D_inSource::setup(){
	// Give our source a decent name
    name = "D_in Source";
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    dice.load(fname);
    imageInSetup();
    imageOutSetup();
}
//--------------------------------------------------------------
void D_inSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}
//--------------------------------------------------------------
void D_inSource::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D_inSource::callFileName(string _fileName){
    fname = _fileName;
}

//--------------------------------------------------------------
// Don't do any drawing here
void D_inSource::update(){
    imageInUpdate();
    imageOutUpdate();
    
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D_inSource::draw(){
    ofClear(0);//clear the buffer
    //Clears the color and depth bits of current renderer and replaces it with an ofColor
    
    imageIn();
    if(tIn>=180){
        imageOut();
    }
    
}
//==============================================================
void D_inSource::imageInSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tIn = 50;
    alpha = 0;
}
//--------------------------------------------------------------
void D_inSource::imageInUpdate(){
    tIn+=0.5;
    if(tIn>=180){
        tIn=180;
        alpha=255;
        //cout<<ofGetFrameNum()<<endl; //this source finish at 260 frame
    }
}
//--------------------------------------------------------------
void D_inSource::imageIn(){
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i;
        a = sin(ofDegToRad(90/tileNum*i+tIn))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tIn<<endl;
    }
    //seperating in and out
    ofSetColor(0,0,0,alpha);
    ofDrawRectangle(0, 0, w, h);
}
//==============================================================
void D_inSource::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //move from 280
}
//--------------------------------------------------------------
void D_inSource::imageOutUpdate(){
    if(tIn==180){
        tOut+=0.5;
    }
    if(tOut>=400){
        tOut=400;
    }
}
//--------------------------------------------------------------
void D_inSource::imageOut(){
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i+t;
        a = sin(ofDegToRad(90/tileNum*i+tOut))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tOut<<endl;
    }
    //ofSetColor(255);
    //ofDrawCircle(w/2, h/2, w/8);
}
