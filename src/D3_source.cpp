#include "D3_source.h"

void D3_source::setup(){
	// Give our source a decent name
    name = "D3_ Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    groupDotsSetup();
    
    dice.load("dice3.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D3_source::reset(){
    startTime = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void D3_source::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D3_source::timer(float nn){
    n = nn;
}
//--------------------------------------------------------------
void D3_source::update(){
    imageOutUpdate();
    //run the animation after image out
    if(tOut>=400){
    t+=1;
    groupDotsUpdate();
    }
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D3_source::draw(){
    //ofClear(0);//clear the buffer
    
    float elapsed  = ofGetElapsedTimeMillis()-startTime;
    if (elapsed > n) {
        ofSetColor(0,0,0,10);
        ofDrawRectangle(0,0,w,h);
        
        ofPushMatrix();
        ofTranslate(w/4+w+w/8, h/2-h/6);
        ofPushMatrix();
        ofRotateDeg(135);
        sinWave();
        ofPopMatrix();
        ofPopMatrix();
        
        zoomCircles();
        
        if(t>60*10){ //main animation last about 17s
            sceneExit();
        }
    }
    
    imageOut();
}

//--------------------------------------------------------------
void D3_source::zoomCircles(){
    //three big zooming circles
    for (int i=0; i<3; i+=1){
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
        float r = 100 * abs(sin(ofDegToRad(55+t)));
        ofDrawCircle(w/4*3-i*w/4, h/4+i*h/4, r);
        ofPopStyle();
        
        //inside each big circle draw a running groupDots
        ofPushMatrix();
        ofTranslate(w/4*3-i*w/4,h/4+i*h/4);
        ofPushMatrix();
        //groupDots scale vary same as the big circle
        ofScale(abs(sin(ofDegToRad(55+t))),abs(sin(ofDegToRad(55+t))));
        groupDots();
        ofPopMatrix();
        ofPopMatrix();
    }
}
//--------------------------------------------------------------
void D3_source::groupDotsSetup(){
    dotNum = 4;
    for (int i = 0; i < dotNum; i++) {
        noiseSeeds.push_back(ofRandom(0, 1000));
    }
}
//---
void D3_source::groupDotsUpdate(){
    for (int i=0; i<dotNum; i++){
        noiseSeeds[i] += 0.01;
    }
}
//---
void D3_source::groupDots(){
    for(int j; j<dotNum; j++){
        ofPoint CenterLoc;
        CenterLoc.x = cos(ofDegToRad(360./5*j)) ;
        CenterLoc.y = sin(ofDegToRad(360./5*j)) ;
        
        ofPoint offset;
        offset.x = ofSignedNoise(noiseSeeds[j]) * 100 ;
        offset.y = ofSignedNoise(noiseSeeds[j]+70) * 100 ;
        
        ofPoint newPoint;
        newPoint = CenterLoc + offset;
        
        float pointSize;
        pointSize = ofSignedNoise(noiseSeeds[j]+100)* 20 +5;
        
        ofSetColor(255);
        ofDrawCircle(newPoint, pointSize);
    }
}

//--------------------------------------------------------------
void D3_source::sinWave(){
    
    width = w/1.5/360.;
    
    for (int j=0; j<w+w/3; j+=w/1.5){
        for (int i=0; i<360; i+=10){
            length = 75 * sin(ofDegToRad(i-t));
            rad = 3 * sin(ofDegToRad(i+t));
            
            ofSetLineWidth(1.5);
            ofSetColor(255* abs(sin(ofDegToRad(i-t))));
            
            ofDrawLine(i*width+j, h+120, i*width+j, h/2-length);
            //ofDrawCircle(i*width+j, h/2-length, rad, rad);
            
            length2 = 75 * sin(ofDegToRad(i+185-t));
            ofDrawLine(i*width+j+5, -120, i*width+j+5, h/2-length2);
            //ofDrawCircle(i*width+j+5, h/2-length2, rad, rad);
        }
    }
}
//==============================================================
void D3_source::sceneExit(){
    radExit+=7;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}
//==============================================================
void D3_source::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    clearColor = 255;
}
//--------------------------------------------------------------
void D3_source::imageOutUpdate(){
    tOut+=0.5;
    
    if(tOut>=400){
        tOut=400;
        clearColor = 0;
    }
}
//--------------------------------------------------------------
void D3_source::imageOut(){
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
