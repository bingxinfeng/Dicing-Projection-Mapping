#include "D_stillSource.h"

void D_stillSource::setup(){
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
}
//--------------------------------------------------------------
void D_stillSource::reset(){
    //reset is called optionally. if you leave it empty nothing is happening
    //rectColor = ofColor(ofRandom(255),ofRandom(255),ofRandom(255));
}
//--------------------------------------------------------------
void D_stillSource::setName(string _name){
    name = _name;
}
//--------------------------------------------------------------
void D_stillSource::callFileName(string _fileName){
    fname = _fileName;
}
//--------------------------------------------------------------
// Don't do any drawing here
void D_stillSource::update(){
}
//--------------------------------------------------------------
// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void D_stillSource::draw(){
    ofClear(0);//clear the buffer
    //Clears the color and depth bits of current renderer and replaces it with an ofColor
   dice.drawSubsection(0, 0, w, h, 0, 0);
}
