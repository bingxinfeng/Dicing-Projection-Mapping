#include "D6_source.h"

void D6_source::setup(){
	// Give our source a decent name
    name = "D6_ Source";
	// Allocate our FBO source, decide how big it should be
    allocate(500, 500);
    
    //my setup code here -----------------------
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetCircleResolution(50);
    w = fbo->getWidth();
    h = fbo->getHeight();
    
    t=0;
    floatingUnitSetup();
    threeVerticalCirclesSetup();
    
    dice.load("dice6.jpg");
    imageOutSetup();
}
//--------------------------------------------------------------
void D6_source::reset(){
    startTime = ofGetElapsedTimeMillis();
}
//--------------------------------------------------------------
void D6_source::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D6_source::timer(float nn){
    n = nn;
}
//--------------------------------------------------------------
void D6_source::update(){
    imageOutUpdate();
    //run the animation after image out
    if(tOut>=400){
        t++;
        floatingUnitUpdate();
        threeVerticalCirclesUpdate();
    }
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D6_source::draw(){
    //ofClear(0);//clear the buffer
    
    float elapsed  = ofGetElapsedTimeMillis()-startTime;
    //if (elapsed > n) {
        //transparent bg
        ofSetColor(0, 0, 0,ofMap(amtT,0,60*6,10,70));
        ofDrawRectangle(0,0,w,h);
        
        threeVerticalCircles();
        
        //mirror the 3 circles line
        ofPushMatrix();
        ofTranslate(w,h);
        ofPushMatrix();
        ofRotateYDeg(-180); //from right to left Yrotate: -180
        ofPushMatrix();
        ofRotateXDeg(180);  //from up to down Xrotate: 180
        threeVerticalCircles();
        
        ofPopMatrix();
        ofPopMatrix();
        ofPopMatrix();
    
    if(t>60*16){ //main animation last about 17s
        sceneExit();
    }
    
    imageOut();
    //}
}
//--------------------------------------------------------------
void D6_source::floatingUnitSetup(){
    numOfPoints = 150;
    radius = 50; //the big circle rad
    angleStep = 360.0 / numOfPoints;
    amtT=0;
    
    for (int i = 0; i < numOfPoints; i++) {
        noiseSeeds.push_back(ofRandom(0, 1000));
    }
}
//-------
void D6_source::floatingUnitUpdate(){
    for (int i=0; i<numOfPoints; i++){
        noiseSeeds[i] += 0.01;
    }
}
//-------
void D6_source::floatingUnit(){
    //translate to the big circle's center point (x,y)
    ofPushMatrix();
    ofTranslate(w/2, h/2);
    ofRotateDeg(t/2);
    
    //ofPushMatrix();
    float s = ofMap(amtT,0,60*6,1,2);
    if(amtT==0){
        ofScale(1,1);
    }
    if(amtT>0){
        ofScale(s,s);
    }
    
    for (int i=0; i<numOfPoints; i++){
        //the 'correct' location
        ofPoint pointLocation;
        pointLocation.x = cos(ofDegToRad(angleStep*i)) * radius;
        pointLocation.y = sin(ofDegToRad(angleStep*i)) * radius;
        
        float amt = ofMap(amtT, 0, 60*6, 0, 80, true);
        
        //random moving distance
        ofPoint offset;
        offset.x = ofSignedNoise(noiseSeeds[i]) * amt;
        offset.y = ofSignedNoise(noiseSeeds[i] + 55) * amt;
        //offset = ofPoint(x, y);
        
        //the final point calculation
        ofPoint newPoint;
        newPoint = pointLocation + offset;
        
        float pointSize;
        pointSize = ofSignedNoise(noiseSeeds[i])* 12 ;
        
        ofColor c1(150 , 150 ,150);
        ofColor c2(255, 255, 255);
        ofColor c3 = c1.getLerped(c2, noiseSeeds[i]);
        ofSetColor(c3);
        
        ofDrawCircle(newPoint, pointSize);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void D6_source::threeVerticalCirclesSetup(){
    mt1=0;
    mt2=0;
}
//--------
void D6_source::threeVerticalCirclesUpdate(){
    mt1++;
    if (mt1>=60*3){
        mt1=60*3;
        mt2++;
    }
    if (mt2>=60*3){
        mt2=60*3;
        mt3++;
    }
    if (mt3>=60*3){
        mt3=60*3;
        amtT++;
    }
}
//--------
void D6_source::threeVerticalCircles(){
    
    //The 1st point, move from center to right
    ofPoint toLoc1;
    toLoc1.x = ofMap(mt1,0,60*3,0,w/6);
    toLoc1.y = 0;
    ofPushMatrix();
    ofTranslate(toLoc1);
    floatingUnit();
    
    //The 2nd point, based on 1st location, move from right to above
    ofPoint toLoc2;
    toLoc2.x = 0;
    toLoc2.y = ofMap(mt2,0,60*3,0,-h/3.5);
    ofPushMatrix();
    ofTranslate(toLoc2);
    floatingUnit();
    
    //The 3rd point, based on 2nd location, move from above to left
    ofPoint toLoc3;
    toLoc3.x = ofMap(mt3,0,60*3,0,-w/3);
    toLoc3.y = 0;
    ofPushMatrix();
    ofTranslate(toLoc3);
    floatingUnit();
    ofPopMatrix(); //3rd
    ofPopMatrix(); //2nd
    ofPopMatrix(); //1st
}
//==============================================================
void D6_source::imageOutSetup(){
    tileNum = 10;
    spacing = w/tileNum;
    tOut = 260; //start moving from 280
    clearColor = 255;
}
//--------------------------------------------------------------
void D6_source::imageOutUpdate(){
    tOut+=0.5;
    
    if(tOut>=400){
        tOut=400;
        clearColor = 0;
    }
}
//--------------------------------------------------------------
void D6_source::imageOut(){
    
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
void D6_source::sceneExit(){
    radExit+=7;
    ofSetColor(0);
    ofDrawCircle(w/2, h/2, radExit);
}

