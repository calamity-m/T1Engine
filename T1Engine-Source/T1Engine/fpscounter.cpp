#include "fpscounter.h"

fpscounter::fpscounter() {
	frames = 0;
	base = glutGet(GLUT_ELAPSED_TIME);
}

void fpscounter::init() {
	frames = 0;
	base = glutGet(GLUT_ELAPSED_TIME);
}

float fpscounter::getFPS() {

	float fps = 0;
	float currTime = glutGet(GLUT_ELAPSED_TIME);
	frames += 1;
	if (currTime - base >= 1000) {
		fps = frames*1000.0 / (currTime - base);
		frames = 0;
		base = currTime;

	}

	return fps;
}

void fpscounter::displayFPSTitle(char * title) {
	float fps = getFPS();

	char buff[256];

	if (fps > 0) {
		sprintf(buff, "%s | FPS: %.2f", title, fps);
		glutSetWindowTitle(buff);
	}
}
