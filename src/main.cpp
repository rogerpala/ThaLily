#include "ofAppGlutWindow.h"
#include "testApp.h"

int framesPerFrame = 60;
int framesPerTransition = 60;
bool goingForward = true;
int targetFrame = 1;
bool DEBUG = true;

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1080, 1920, OF_WINDOW);
	ofRunApp(new testApp());
}
