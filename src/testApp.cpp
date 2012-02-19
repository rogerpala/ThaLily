#include "testApp.h"

extern int framesPerFrame;
extern int framesPerTransition;
extern bool goingForward;
extern int targetFrame;

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
	posX = ofGetWindowWidth() - camWidth;
	posY = ofGetWindowHeight() - camHeight;
	
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	//videoInverted 	= new unsigned char[camWidth*camHeight*3];
	//videoTexture.allocate(camWidth,camHeight, GL_RGB);
	haarFinderMinWidth = 0;
	haarFinderMinHeight = 0;
	
	//img.loadImage("test.jpg");
	finder.setScaleHaar(1.5);
	finder.setup("haarcascade_frontalface_default.xml");
	
	gui.addTitle("HAAR SETTINGS");
	gui.addSlider("haarFinderMinWidth", haarFinderMinWidth, 0, 320);
	gui.addSlider("haarFinderMinHeight", haarFinderMinHeight, 0, 240);
	gui.addSlider("viewerLevel", viewerLevel, 0, 2000);
	gui.addSlider("framesPerFrame", framesPerFrame, 1, 60*5);
	gui.addSlider("framesPerTransition", framesPerTransition, 1, 60*5);
	gui.addToggle("goingForward", goingForward);
	gui.loadFromXML();
	gui.show();
	
	frameCount = 0;
	viewerLevel = 0;
	framesPerFrame = 10;
	framesPerTransition = 100;
	
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
	
	vidGrabber.draw(posX, posY);
	ofNoFill();
	for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(posX + cur.x, posY + cur.y, cur.width, cur.height);
		if(viewerLevel < 380) {
			viewerLevel++;
			goingForward = true;
		}
	}
	
	if(finder.blobs.size() == 0 && viewerLevel > 0) {
		viewerLevel--;
		goingForward = false;
	}
	
	targetFrame = viewerLevel;
	
	gui.draw();
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