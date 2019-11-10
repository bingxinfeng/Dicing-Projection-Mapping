#include "D1_03noImgSource.h"

void D1_03noImgSource::setup(){
	// Give our source a decent name
    name = "D1_03 noImg Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    locX = 0;
    locY = 0;
    t = 0;
    brightness = 255;
    radExit=0;
    
    dice.load("dice1.jpg");
    imageOutSetup();
    
    boucingCenterCircleSetup();
    centerWaveSetup();
}
//--------------------------------------------------------------
void D1_03noImgSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}
//--------------------------------------------------------------
void D1_03noImgSource::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
// Don't do any drawing here
void D1_03noImgSource::update(){
    
    //imageOutUpdate();
    //if(tOut==400){
        t+=1;
        //boucingCenterCircleUpdate();
        centerWaveUpdate();
    //}
    
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D1_03noImgSource::draw(){
    ofClear(0);//clear the buffer
    
    //boucingCenterCircle();
    
    //if(tCenter==360*2){
        centerWave();
    //}
    
    if(t>9*60){ //main animation last about 17s
        sceneExit();
    }
    
    //imageOut();
    
    //cout<<t<<endl;
    
}

//==============================================================
void D1_03noImgSource::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    underDotColor = 255;
}
//--------------------------------------------------------------
void D1_03noImgSource::imageOutUpdate(){
    tOut+=0.5;
    if(tOut>=400){
        tOut=400;
        underDotColor = 0;
    }
}
//--------------------------------------------------------------
void D1_03noImgSource::imageOut(){
    
    //centerDot under the image layer
    ofSetColor(255,255,255,underDotColor);
    ofDrawCircle(w/2, h/2, w/8);
    
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
void D1_03noImgSource::boucingCenterCircleSetup(){
    r = w/8;
    tCenter=90;
}
//--------------------------------------------------------------
void D1_03noImgSource::boucingCenterCircleUpdate(){
    //here is how to stop a sin movement
    float deg=360*2; //(0=0,90=1,180=0,270=-1,360=0), deg*loopTimes
    if(tCenter<deg){
        tCenter+=2;
    }
    if(tCenter>=deg){
        tCenter=deg;
    }
}
//--------------------------------------------------------------
void D1_03noImgSource::boucingCenterCircle(){
    
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    
    float a = abs(sin(ofDegToRad(t)));
    float scale = ofMap(a,0,1,1,0);
    ofScale(scale, scale);
    
    brightness = ofMap(a,0,1,255,0);
    ofSetColor(brightness);
    ofDrawCircle(locX,locY,r);
    
    ofPopMatrix();
}

//==============================================================
void D1_03noImgSource::centerWaveSetup(){
    tScale=0;
    noiseSeed=0;
}
//--------------------------------------------------------------
void D1_03noImgSource::centerWaveUpdate(){
    //if(tCenter==360*2){
        tScale+=1;
        if(tScale>=180){
            tScale=180;
        }
    //}
    noiseSeed+=0.01;
}
//--------------------------------------------------------------
void D1_03noImgSource::centerWave(){
    
    ofPushMatrix();
    
    float s=ofMap(tScale,0,180,0,1);
    ofTranslate(w/2, h/2);
    ofScale(s,s);
    
    //ofSetColor(255);
    //ofSetRectMode(OF_RECTMODE_CENTER);
    //ofDrawRectangle(0, 0, w, h); //background square
    
    float ringNum = 10;
    float spacing = w/(ringNum*2);
    
    for (int i=0; i<ringNum; i++){
        float r=w/2-i*spacing;
        
        //the still white circles
        ofFill();
        ofSetColor(255);
        ofDrawCircle(locX,locY,r+2);
        
        float a = sin(ofDegToRad(t+i*360/ringNum));
        float scale = ofMap(a,-1,1,0,.3)+0.7;
        
        //detailed lines circles
        ofPushMatrix();
        ofScale(scale, scale);
        ofSetColor(100,100,100,brightness);
        ofNoFill();
        ofDrawCircle(locX,locY,r+ofNoise(noiseSeed)*50);
        ofPopMatrix();
        
        //the main black varing circles
        ofPushMatrix();
        ofScale(scale, scale);
        //brightness = ofMap(a,-1,1,255,0);
        ofSetColor(0);
        ofFill();
        //SetColor(0);
        ofDrawCircle(locX,locY,r);
        ofPopMatrix();
    }
    
    ofPopMatrix();
}
//==============================================================

void D1_03noImgSource::sceneExit(){
    radExit+=5;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}
