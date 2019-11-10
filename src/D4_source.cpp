#include "D4_source.h"

void D4_source::setup(){
	// Give our source a decent name
    name = "D4_ Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    white = 255;
    black = 0;
    
    floatingsUnitSetup();
    bouncingBallSetup();
    
    dice.load("dice4.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D4_source::reset(){
    startTime = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void D4_source::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D4_source::timer(float nn){
    n = nn;
}
//--------------------------------------------------------------
void D4_source::update(){
    imageOutUpdate();
    //run the animation after image out
    if(tOut>=400){
        floatingsUnitUpdate();
        bouncingBallUpdate();
    }
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D4_source::draw(){
    //ofClear(0);//clear the buffer
    
    float elapsed  = ofGetElapsedTimeMillis()-startTime;
    //if (elapsed > n) {
        
        floatingsUnit();
        bouncingBallDraw();
        
        //mirror floatingUnit
        ofPushMatrix();
        ofTranslate(w/2, h/2);
        floatingsUnit();
        ofPopMatrix();
        
        //mirror bouncingBallDraw
        ofPushMatrix();
        ofTranslate(w/2, -h/2);
        bouncingBallDraw();
        ofPopMatrix();
    
        if(t>60*15){ //main animation last about 17s
            sceneExit();
        }
    
        imageOut();
    }
//}

//--------------------------------------------------------------
void D4_source::floatingsUnitSetup(){
    locX = 0;
    locY = 0;
    r = w/8;
    t = 0;
    numOfPoints = 4;
    radius = 20; //the big circle rad
    angleStep = 360.0 / numOfPoints;
    
    for (int i = 0; i < numOfPoints; i++) {
        noiseSeeds.push_back(ofRandom(0, 1000));
    }
}
//------
void D4_source::floatingsUnitUpdate(){
    
    t+=1;
    degT++;
    
    for (int i=0; i<numOfPoints; i++){
        noiseSeeds[i] += 0.01;
    }
}
//-------
void D4_source::floatingsUnit(){
    //move the whole floatingUnit to the left top corner
    ofPushMatrix();
    ofTranslate(-w/4, -h/4);
    
    //square blockUnit under the unit
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    ofSetColor(black,black,black,15);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawRectangle(0, 0, w/2,h/2);
    ofPopMatrix();
    
    //location for the whole unit moving
    ofPoint Move;
    Move.x = cos(ofDegToRad(360+degT)) * w/7;
    Move.y = sin(ofDegToRad(360+degT)) * w/7;
    ofPushMatrix();
    ofTranslate(Move);
    //360 is the right side, 0 is the left side, if only x/y =degT, it's moving horizontally/vertically.
    
    //translate to the big circle's center point (x,y) (only for the unit)
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    ofPushMatrix();
    ofRotateDeg(t/2);
    
    //drawing the floating unit
    for (int i=0; i<numOfPoints; i++){
        //the outline location before adding random offset
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * radius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * radius;
        
        amt = 30;
        
        //random moving distance
        ofPoint offset;
        offset.x = ofSignedNoise(noiseSeeds[i]) * amt;
        offset.y = ofSignedNoise(noiseSeeds[i] + 55) * amt;
        
        //the final point calculation
        ofPoint newPoint;
        newPoint = pointLocation + offset;
        
        float pointSize;
        pointSize = ofSignedNoise(noiseSeeds[i])* 50+10;
        
        ofColor c1(250, 250 ,250);
        ofColor c2(255, 255, 255);
        ofColor c3 = c1.getLerped(c2, noiseSeeds[i]);
        ofSetColor(c3);
        
        ofDrawCircle(newPoint, pointSize);
    }
    ofPopMatrix(); //rotate t/2
    ofPopMatrix(); //tanslate w/2 h/2
    ofPopMatrix(); //move move
    ofPopMatrix(); //-w/4 -h/4
}
//--------------------------------------------------------------
void D4_source::bouncingBallSetup(){
    bb.x = w/4;
    bb.y = h/4*3;
    bbRad = 5;
    
    sp.x = 2;
    sp.y = 2.5;
}
//-------
void D4_source::bouncingBallUpdate(){
    bb.x=bb.x+sp.x;
    bb.y=bb.y+sp.y;
    //brightnessCheck();
    if(bb.x<0+bbRad+2||bb.x>w/2-bbRad-2) {
        sp.x *= -1;
        brightnessCheck();
    }
    if(bb.y<h/2+bbRad+2||bb.y>h-bbRad-2) {
        sp.y *= -1;
        brightnessCheck();
    }
}
//-------
void D4_source::bouncingBallDraw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(white,white,white,10);
    //ofDrawRectangle(w/4, h/4*3, w/2,h/2);
    ofSetColor(black);
    ofDrawCircle(bb, bbRad);
    cout<<black<<endl;
}
//--------------------------------------------------------------
void D4_source::brightnessCheck(){
    white = abs(white-255);
    black = abs(black-255);
}
//==============================================================
void D4_source::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    clearColor = 255;
}
//--------------------------------------------------------------
void D4_source::imageOutUpdate(){
    tOut+=0.5;
    
    if(tOut>=400){
        tOut=400;
        clearColor = 0;
    }
}
//--------------------------------------------------------------
void D4_source::imageOut(){
    ofPushMatrix();
    ofTranslate(25, h/2); //fix the translation problem
    
    ofSetColor(0,0,0,clearColor);
    ofDrawRectangle(0, 0, 3*w, 3*h);
    
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
void D4_source::sceneExit(){
    radExit+=7;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}
