/*
 *  VideoManager.h
 *  opencvHaarFinderExample
 *
 *  Created by Roger Palà on 16/11/2011.
 *  Copyright 2011 B-Reel. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "CppTweener.h"

class VideoManager: public tween::TweenerListener{
public:
	VideoManager();
	void update();
	void draw();
	
	tween::Tweener tweener;
	void onStart(tween::TweenerParam& param) ;
	void onStep(tween::TweenerParam& param) ;
	void onComplete(tween::TweenerParam& param);
	void startTransition();
	
	void swapMovies(ofVideoPlayer*& a, ofVideoPlayer*& b);
	
	
	ofVideoPlayer 		mov1, mov2;
	ofVideoPlayer* from;
	ofVideoPlayer* to;
	
	
	
	int framesCount;
	int totalFrames;
	
	bool isTransitioning;
	bool frameRendered;
	float fakeTweenValue;
	
	float time;
	float xfade;
	
	
};
