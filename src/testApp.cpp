#include "testApp.h"

extern int framesPerFrame;
extern int framesPerTransition;
extern bool goingForward;
extern int targetFrame;
extern bool DEBUG;

int NUM_INTRO_FRAMES = 180;
int TOTAL_FRAMES = 1481;
int FRAMES_PER_FRAME_INTRO = 1;
int FRAMES_PER_TRANSITION_INTRO = 1;
int FRAMES_PER_FRAME = 10;
int FRAMES_PER_TRANSITION = 100;
int DEFAULT_HAAR_MIN_WIDTH = 50;
int DEFAULT_HAAR_MIN_HEIGHT = 75;

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofBackground(0, 0, 0, 255);
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	posX = ofGetWindowWidth() - camWidth;
	posY = 0;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	//videoInverted 	= new unsigned char[camWidth*camHeight*3];
	//videoTexture.allocate(camWidth,camHeight, GL_RGB);
	haarFinderMinWidth = 0;
	haarFinderMinHeight = 0;
	
	//img.loadImage("test.jpg");
	finder.setScaleHaar(1.5);
	finder.setup("haarcascade_frontalface_default.xml");
	
	if(DEBUG){
		gui.addTitle("HAAR SETTINGS");
		gui.addSlider("haarFinderMinWidth", haarFinderMinWidth, 0, 320);
		gui.addSlider("haarFinderMinHeight", haarFinderMinHeight, 0, 240);
		gui.addSlider("viewerLevel", viewerLevel, 0, 2000);
		gui.addSlider("framesPerFrame", framesPerFrame, 1, 60*5);
		gui.addSlider("framesPerTransition", framesPerTransition, 1, 60*5);
		gui.addToggle("goingForward", goingForward);
		gui.loadFromXML();
		gui.show();
	}else {
		haarFinderMinWidth = DEFAULT_HAAR_MIN_WIDTH;
		haarFinderMinHeight = DEFAULT_HAAR_MIN_HEIGHT;
	}

	
	frameCount = 0;
	viewerLevel = 0;
	isIntroPlayed = false;
	
	framesPerFrame = FRAMES_PER_FRAME_INTRO;
	framesPerTransition = FRAMES_PER_TRANSITION_INTRO;
	targetFrame = NUM_INTRO_FRAMES;
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	vidGrabber.grabFrame();
	
	if (vidGrabber.isFrameNew() && frameCount > 10){
		finder.findHaarObjects(vidGrabber.getPixelsRef(), haarFinderMinWidth, haarFinderMinHeight);
		frameCount = 0;
	}
	frameCount++;
	
	videoManager.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	
	videoManager.draw();
	
	if(isIntroPlayed){
		if(DEBUG) vidGrabber.draw(posX, posY);
		ofNoFill();
		for(int i = 0; i < finder.blobs.size(); i++) {
			ofRectangle cur = finder.blobs[i].boundingRect;
			if(DEBUG) ofRect(posX + cur.x, posY + cur.y, cur.width, cur.height);
			if(viewerLevel > 0) {
				viewerLevel--;
				goingForward = false;
			}
		}
		
		if(finder.blobs.size() == 0 && viewerLevel < TOTAL_FRAMES - NUM_INTRO_FRAMES) {
			viewerLevel++;
			goingForward = true;
		}
		targetFrame = viewerLevel + NUM_INTRO_FRAMES;
	}else {
		if (videoManager.frameNumber == NUM_INTRO_FRAMES) {
			isIntroPlayed = true;
			framesPerFrame = FRAMES_PER_FRAME;
			framesPerTransition = FRAMES_PER_TRANSITION;
		}
	}

	
	
	if(DEBUG) gui.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if (key == 'g') {
		gui.toggleDraw();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}