////////////////////////////////////////////////////////////////
//															  //
// Based off of:											  //
// glutWindow.h                                               //
// beta version 0.3 - 9/9/97)                                 //
//                                                            //
// George Stetten and Korin Crawford                          //
// copyright given to the public domain                       //
//                                                            //
// Please email comments to email@stetten.com                 //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef glutscene_h
#define glutscene_h
#pragma once

#include <iostream>
#include <stdlib.h>
#include "glut.h"

class GlutScene {

public:

	int windowWidth, windowHeight;
	bool timeForNextFrame;

	GlutScene(void) { };
	~GlutScene() { };

	
	virtual void Render() { };
	virtual void Update() { };
	virtual void EnterScene() { 

		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	
	};
	virtual void ExitScene() { };
	virtual void ASCII(unsigned char key, int x, int y) { };
	virtual void ASCIIUp(unsigned char key, int x, int y) { };
	virtual void SpecialKey(int key, int x, int y) { };
	virtual void SpecialKeyUp(int  key, int  x, int  y) { };
	virtual void Motion(int x, int y) { };
	virtual void Mouse(int button, int state, int x, int y) { };
	virtual void PassiveMotion(int x, int y) { };
	virtual void Visibility(int v) { };
	virtual void Resize(int w, int h) {
		windowWidth = w;
		windowHeight = h;

		glViewport(0, 0, windowWidth, windowHeight);
	};
	virtual void Timer(int v) {
		timeForNextFrame = true;
	};
	void Initalize() {
		// Set Polygon Mode to Wireframe
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Required for Vertex Arrays
		glEnableClientState(GL_VERTEX_ARRAY);

		glEnable(GL_DEPTH_TEST);

		// Enable backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
	};
	void Clear() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void CheckAndSwapBuffers() {
		int err;
		char msg[256];
		err = glGetError();
		if (err != GL_NO_ERROR) {
			printf("broekn cunt\n");
			sprintf(msg, "OpenGL error: %s", gluErrorString(err));
			fprintf(stderr, "%s\n", msg);
			//exit(1);
		}
		else {
			glutSwapBuffers();
		}
	}
	void SetProjection(float fov, float n, float f) {
		GLfloat aspectRatio;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		aspectRatio = (float)windowWidth / (float)windowHeight;
		gluPerspective(fov, aspectRatio, n, f);
		glMatrixMode(GL_MODELVIEW);
	};
};

#endif // !glutscene_h


