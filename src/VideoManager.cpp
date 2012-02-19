/*
 *  VideoManager.cpp
 *  opencvHaarFinderExample
 *
 *  Created by Roger Palà on 16/11/2011.
 *  Copyright 2011 B-Reel. All rights reserved.
 *
 */

#include "VideoManager.h"

extern int framesPerFrame;
extern int framesPerTransition;
extern bool goingForward;
extern int targetFrame;

int frameNumber;


//--------------------------------------------------------------
VideoManager::VideoManager(){
		
	
	string videoPath = ofToDataPath("fingers.mov");
	
	
	
	
	
	mov1.setPixelFormat(OF_PIXELS_RGB);
	mov2.setPixelFormat(OF_PIXELS_RGB);
	
	
	ofDisableDataPath();
	mov1.loadMovie("data/lily.mov");
	mov2.loadMovie("data/lily.mov");
	ofEnableDataPath();
	
		
	from = &mov1;
	to = &mov2;
	
	xfade = 1.0;
	framesPerFrame = 60 * 3;
	framesPerTransition = 60;
	framesCount = 0;
	isTransitioning = false;
	frameRendered = false;
	time = 0;
	totalFrames = mov1.getTotalNumFrames();
	frameNumber = 0;
	
	cout << mov1.getTotalNumFrames() << endl;


	
}

//--------------------------------------------------------------
void VideoManager::update(){
    mov1.update();
	mov2.update();
	
	tweener.step(ofGetElapsedTimeMillis());
	
	//std::swap(from, to);
	
	if(!frameRendered){
		if(targetFrame > frameNumber){
			frameNumber++;
			from->setFrame(frameNumber);
			to->setFrame(frameNumber+1);
		}else {
			frameNumber--;
			from->setFrame(frameNumber);
			to->setFrame(frameNumber-1);
		}
		
		
		cout << "from FrameNumber: " << from->getCurrentFrame() << endl;
		cout << "to FrameNumber: " << to->getCurrentFrame() << endl;
		framesCount = 0;
		frameRendered = true;
	}else{
		if (framesCount > framesPerFrame) {
			if(!isTransitioning) startTransition();
		}
	}
	framesCount++;
}

void VideoManager::swapMovies(ofVideoPlayer*& a, ofVideoPlayer*& b)
{
    ofVideoPlayer* c = a;
    a = b;
    b = c;
}

void VideoManager::onStart(tween::TweenerParam& param){
	//cout << "onStart!" << std::endl;
	//step = 0;
	isTransitioning = true;
	xfade = 1;
	
} 
void VideoManager::onStep(tween::TweenerParam& param) {
	//std::cout<<"\nStep:"<< param.timeCount / ((framesPerTransition / 60) *1000)<<"\n";
	xfade = 1 - param.timeCount / ((framesPerTransition / 60) *1000);
}
void VideoManager::onComplete(tween::TweenerParam& param){
	//cout << "onComplete!" << std::endl;
	xfade = 0;
	tweener.removeListener(this);
	isTransitioning = false;
	frameRendered = false;
	swapMovies(from, to);
	xfade = 1;
	//cout << "from num frames: " << from->getTotalNumFrames() << std::endl;
	//cout << "to num frames: " << to->getTotalNumFrames() << std::endl;
}

void VideoManager::startTransition()
{	
	
	
	tween::TweenerParam transitionOut((framesPerTransition / 60) *1000, tween::LINEAR, tween::EASE_OUT);
	
	transitionOut.setUseMilliSeconds(true);
	transitionOut.addProperty(&fakeTweenValue, 1);
	
    tweener.addTween(transitionOut); 
	
	tweener.addListener(this);
	
	
	
	
}


//--------------------------------------------------------------
void VideoManager::draw(){

	float aX = ofGetWidth() * 0.5 - mov1.width * 0.5;
	float aY = ofGetHeight() * 0.5 - mov1.height * 0.5;
	//xfade = sin(time);
	//cout<< xfade << endl;
	
	glPushMatrix();
	
	glEnable(GL_BLEND);
	
	// draw first picture
	glColor4f(1.0f, 1.0f, 1.0f, xfade);   
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);   // takes src brightness (ignore dest color)
	from->draw(aX, aY);
	
	// draw second picture
	glColor4f(1.0f, 1.0f, 1.0f, 1.0-xfade);   
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);    // takes the src and add it to the entire dest color
	to->draw(aX, aY);
	
	glPopMatrix();
	
	time+= 0.001;
	
	ofSetHexColor(0xFFFFFF);
	
	
}