#include "D5_source.h"

void D5_source::setup(){
	// Give our source a decent name
    name = "D5_ Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    t = 0;
    floatingUnitSetup();
    
    dice.load("dice5.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D5_source::reset(){
    startTime = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void D5_source::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D5_source::timer(float nn){
    n = nn;
}
//--------------------------------------------------------------
void D5_source::update(){
    imageOutUpdate();
    //run the animation after image out
    if(tOut>=400){
        t+=1;
        floatingUnitUpdate();
    }
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D5_source::draw(){
    //ofClear(0);//clear the buffer
    
    float elapsed  = ofGetElapsedTimeMillis()-startTime;
    if (elapsed > n) {
        //transparent bg
        ofSetColor(0, 0, 0, 10);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofDrawRectangle(0,0,w,h);
        
        boucingCenter();
        cornerPoint();
        
        //mirror the corner points
        ofPushMatrix();
        ofRotateYDeg(-180);
        ofTranslate(-w,0);
        cornerPoint();
        ofPopMatrix();
        
        ofPushMatrix();
        ofRotateXDeg(180);
        ofTranslate(0,-h);
        cornerPoint();
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(w,h);
        ofRotateYDeg(-180); //from right to left Yrotate: -180
        ofRotateXDeg(180);  //from up to down Xrotate: 180
        cornerPoint();
        ofPopMatrix();
        
        if(t>60*12){ //main animation last about 17s
            sceneExit();
        }
        
        imageOut();
        }
}

//--------------------------------------------------------------
void D5_source::cornerPoint(){
    //2. use translate to move this circle
    float a = abs(sin(ofDegToRad(t-25)));
    float adjustX = 70;
    float adjustY = 20;
    ofPoint cornerPointLoc;
    cornerPointLoc.x = ofMap(a, 0, 1, w/2-adjustX, w/5-adjustX);
    cornerPointLoc.y = ofMap(a, 0, 1, h/2-adjustY, h/5-adjustY);
    
    ofPushMatrix();
    ofTranslate(cornerPointLoc);
    
    //1. random offset one circle
    for (int i=0; i<2; i++){
        //the 'correct' location
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * radius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * radius;
        
        //random moving distance
        ofPoint offset;
        offset.x = ofSignedNoise(noiseSeeds[i]) * 30;
        offset.y = ofSignedNoise(noiseSeeds[i]+70) * 30;
        
        //the final point calculation
        ofPoint newPoint;
        newPoint = pointLocation + offset;
        
        float pointSize;
        pointSize = ofSignedNoise(noiseSeeds[i]+100)* 30 + 10 ;
        
        ofPushStyle();
        float a = abs(sin(ofDegToRad(t)));
        float alpha = ofMap(a,0,1,0,255);
        ofColor c1(200, 200 ,200, alpha);
        ofColor c2(255, 255, 255, alpha);
        ofColor c3 = c1.getLerped(c2, noiseSeeds[i]);
        ofSetColor(c3);
        //ofSetColor(255);
        //ofNoFill();
        ofDrawCircle(newPoint, pointSize);
        ofPopStyle();
        
        ofPushStyle();
        ofSetColor(200);
        ofNoFill();
        ofPoint newPoint2;
        newPoint2 = newPoint + offset;
        ofDrawCircle(newPoint2, pointSize);
        ofPopStyle();
    }
    
    ofPopMatrix();
    
}
//--------------------------------------------------------------
void D5_source::boucingCenter(){
    
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    //clear the buffer for the center circle
    ofSetColor(0, 0, 0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    //ofDrawRectangle(0,0,100,100); //need to adjust-shrink the size here later.
    
    float a = abs(sin(ofDegToRad(t)));
    float scale = ofMap(a,0,1,0,1);
    ofScale(scale, scale);
    
    float alpha = ofMap(a,0,1,0,255);
    floatingUnit(alpha);
    
    /*
     //here is how to stop a sin movement
     float deg=360*2; //(0=0,90=1,180=0,270=-1,360=0), deg*loopTimes
     if(tCenter<deg){
     tCenter+=2;
     }
     if(tCenter>=deg){
     tCenter=deg;
     }*/
    ofPopMatrix();
}
//--------------------------------------------------------------
void D5_source::floatingUnitSetup(){
    numOfPoints = 50;
    radius = 50; //the big circle rad
    angleStep = 360.0 / numOfPoints;
    
    for (int i = 0; i < numOfPoints; i++) {
        noiseSeeds.push_back(ofRandom(0, 1000));
    }
}
//-------
void D5_source::floatingUnitUpdate(){
    for (int i=0; i<numOfPoints; i++){
        noiseSeeds[i] += 0.01;
    }
}
//-------
void D5_source::floatingUnit(float alpha){
    
    //translate to the big circle's center point (x,y)
    ofPushMatrix();
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateDeg(t/2);
    
    for (int i=0; i<numOfPoints; i++){
        //the 'correct' location
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * radius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * radius;
        
        //amt = ofMap(amtT, 0, 60*6, 0, 80, true);
        amt = 50;
        
        //random moving distance
        ofPoint offset;
        offset.x = ofSignedNoise(noiseSeeds[i]) * amt;
        offset.y = ofSignedNoise(noiseSeeds[i] + 55) * amt;
        //offset = ofPoint(x, y);
        
        //the final point calculation
        ofPoint newPoint;
        newPoint = pointLocation + offset;
        
        float pointSize;
        pointSize = ofSignedNoise(noiseSeeds[i])* 12 +20 ;
        
        ofColor c1(200, 200 ,200, alpha);
        ofColor c2(255, 255, 255, alpha);
        ofColor c3 = c1.getLerped(c2, noiseSeeds[i]);
        ofSetColor(c3);
        
        ofDrawCircle(newPoint, pointSize);
    }
    ofPopMatrix();
}
//==============================================================
void D5_source::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    clearColor = 255;
}
//--------------------------------------------------------------
void D5_source::imageOutUpdate(){
    tOut+=0.5;
    
    if(tOut>=400){
        tOut=400;
        clearColor = 0;
    }
}
//--------------------------------------------------------------
void D5_source::imageOut(){
    ofPushMatrix();
    ofTranslate(25, h/2); //fix the translation problem
    
    ofSetColor(0,0,0,clearColor);
    ofDrawRectangle(0, 0, 3*w, 3*h); //3* fix the translation problem
    
    for (int i=0; i<tileNum; i++){
        deg = 90/tileNum*i+t;
        a = sin(ofDegToRad(90/tileNum*i+tOut))*120;
        y = ofMap(a,0,120,0,-h*2,true);
        ofSetColor(255);
        dice.drawSubsection(i*spacing, y, spacing, h, i*spacing, 0);
        //cout<<tOut<<endl;
    }
    ofPopMatrix();
}
//==============================================================
void D5_source::sceneExit(){
    radExit+=7;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}

