#include "ofApp.h"

void ofApp::setup(){
	ofBackground(0);
    ofSetFrameRate(60);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

    // Add our BouncingBallsSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
    bouncingBallsSource = new BouncingBallsSource();
    bouncingBallsSource->setup();
    piMapper.registerFboSource(bouncingBallsSource);

    movingRectSource = new MovingRectSource();
    movingRectSource->setup();
    piMapper.registerFboSource(movingRectSource);
    
    //my source add from here==================================
    d_inSource = new D_inSource();
    d_inSource->setup();
    d_inSource->callFileName("dice1.jpg");
    piMapper.registerFboSource(d_inSource);
    d_inSource->setName("Din 1");
    
    d_inSource2 = new D_inSource();
    d_inSource2->setup();
    d_inSource2->callFileName("dice2.jpg");
    piMapper.registerFboSource(d_inSource2);
    d_inSource2->setName("Din 2");
    
    d_inSource3 = new D_inSource();
    d_inSource3->setup();
    d_inSource3->callFileName("dice3.jpg");
    piMapper.registerFboSource(d_inSource3);
    d_inSource3->setName("Din 3");
    
    d_inSource4 = new D_inSource();
    d_inSource4->setup();
    d_inSource4->callFileName("dice4.jpg");
    piMapper.registerFboSource(d_inSource4);
    d_inSource4->setName("Din 4");
    
    d_inSource5 = new D_inSource();
    d_inSource5->setup();
    d_inSource5->callFileName("dice5.jpg");
    piMapper.registerFboSource(d_inSource5);
    d_inSource5->setName("Din 5");
    
    d_inSource6 = new D_inSource();
    d_inSource6->setup();
    d_inSource6->callFileName("dice6.jpg");
    piMapper.registerFboSource(d_inSource6);
    d_inSource6->setName("Din 6");
    //--------------------------------------
    d_stillSource = new D_stillSource();
    d_stillSource->setup();
    d_stillSource->callFileName("dice1.jpg");
    piMapper.registerFboSource(d_stillSource);
    d_stillSource->setName("Dstill 1");
    
    d_stillSource2 = new D_stillSource();
    d_stillSource2->setup();
    d_stillSource2->callFileName("dice2.jpg");
    piMapper.registerFboSource(d_stillSource2);
    d_stillSource2->setName("Dstill 2");
    
    d_stillSource3 = new D_stillSource();
    d_stillSource3->setup();
    d_stillSource3->callFileName("dice3.jpg");
    piMapper.registerFboSource(d_stillSource3);
    d_stillSource3->setName("Dstill 3");
    
    d_stillSource4 = new D_stillSource();
    d_stillSource4->setup();
    d_stillSource4->callFileName("dice4.jpg");
    piMapper.registerFboSource(d_stillSource4);
    d_stillSource4->setName("Dstill 4");
    
    d_stillSource5 = new D_stillSource();
    d_stillSource5->setup();
    d_stillSource5->callFileName("dice5.jpg");
    piMapper.registerFboSource(d_stillSource5);
    d_stillSource5->setName("Dstill 5");
    
    d_stillSource6 = new D_stillSource();
    d_stillSource6->setup();
    d_stillSource6->callFileName("dice6.jpg");
    piMapper.registerFboSource(d_stillSource6);
    d_stillSource6->setName("Dstill 6");
    //--------------------------------------
    d1_outSource = new D1_outSource();
    d1_outSource->setup();
    piMapper.registerFboSource(d1_outSource);
    
    d2_outSource = new D2_outSource();
    d2_outSource->setup();
    piMapper.registerFboSource(d2_outSource);
    
    d3_outSource = new D3_outSource();
    d3_outSource->setup();
    piMapper.registerFboSource(d3_outSource);
    
    d4_outSource = new D4_outSource();
    d4_outSource->setup();
    piMapper.registerFboSource(d4_outSource);
    
    d5_outSource = new D5_outSource();
    d5_outSource->setup();
    piMapper.registerFboSource(d5_outSource);
    
    d6_outSource = new D6_outSource();
    d6_outSource->setup();
    piMapper.registerFboSource(d6_outSource);
    
    d1_03noImgSource = new D1_03noImgSource();
    d1_03noImgSource->setup();
    piMapper.registerFboSource(d1_03noImgSource);
    
    d2_source = new D2_source();
    d2_source->setup();
    piMapper.registerFboSource(d2_source);
    
    d3_source1 = new D3_source();
    piMapper.registerFboSource(d3_source1);
    d3_source1->setName("D3-1");
    d3_source1->timer(3500);
    
    d3_source2 = new D3_source();
    piMapper.registerFboSource(d3_source2);
    d3_source2->setName("D3-2");
    d3_source2->timer(5500);
    
    d3_source3 = new D3_source();
    piMapper.registerFboSource(d3_source3);
    d3_source3->setName("D3-3");
    d3_source3->timer(6500);
    
    d4_source = new D4_source();
    piMapper.registerFboSource(d4_source);
    
    d5_source = new D5_source();
    piMapper.registerFboSource(d5_source);
    
    d5_source2 = new D5_source();
    piMapper.registerFboSource(d5_source2);
    d5_source2->setName("d5_source2");
    d5_source2->timer(5000);
    
    d6_source = new D6_source();
    piMapper.registerFboSource(d6_source);
    
    //only need one this setup after all sources
	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

    dummyObjects.load("dummy-objects.png");

    //setup sceneManager to handle scene/present changes automatically
    sceneManager.setup("scenes.json", &piMapper);
}
//-----------------------------------------------------------
void ofApp::update(){
	piMapper.update();
    sceneManager.update();
    if (ofGetElapsedTimeMillis() >= 129000 ) ofExit();
}
//-----------------------------------------------------------
void ofApp::draw(){
    //dummyObjects.draw(0,0);
    piMapper.draw();
}
//-----------------------------------------------------------
void ofApp::keyPressed(int key){
    //press 5 to go to previous preset (scene)
    if (key=='5') {
        if (piMapper.getNumPresets()>1){
            int targetScene = piMapper.getActivePresetIndex() - 1;
            if (targetScene<0) targetScene = piMapper.getNumPresets()-1;
            piMapper.setPreset(targetScene);
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    //press 6 to go to next preset (scene)
    else if (key=='6') {
        if (piMapper.getNumPresets()>1){
            piMapper.setNextPreset();
            cout << "Switched to preset: " << piMapper.getActivePresetIndex() << endl;
        } else cout << "only one preset available" << endl;
    }
    else if (key == '7'){
        piMapper.cloneActivePreset();
        piMapper.setPreset(piMapper.getNumPresets()-1);
        cout << "Cloned and switched to preset: " << piMapper.getActivePresetIndex() << endl;
    }

	piMapper.keyPressed(key);
}
//-----------------------------------------------------------
void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}
//-----------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}
//-----------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}
//-----------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}
