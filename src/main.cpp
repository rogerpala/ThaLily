#include "ofAppGlutWindow.h"
#include "testApp.h"

int framesPerFrame = 60;
int framesPerTransition = 60;
bool goingForward = true;
int targetFrame = 1;

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 984, 983, OF_WINDOW);
	ofRunApp(new testApp());
}
