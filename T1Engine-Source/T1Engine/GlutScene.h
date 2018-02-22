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

/* Base class for all scene objects */
class GlutScene {

public:

	// Width and height of current window
	int windowWidth, windowHeight;
	bool timeForNextFrame;

	GlutScene(void) { };
	~GlutScene() { };

	// Called every render/draw call
	virtual void Render() { };
	// Called every frame
	virtual void Update() { };
	// Called on scene enter
	virtual void EnterScene() { 

		windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
	
	};
	// Called on scene exit
	virtual void ExitScene() { };
	// Wrapper function for glut ASCII calls
	virtual void ASCII(unsigned char key, int x, int y) { };
	// Wrapper function for glut ASCIIUp calls
	virtual void ASCIIUp(unsigned char key, int x, int y) { };
	// Wrapper function for glut SpecialKey calls
	virtual void SpecialKey(int key, int x, int y) { };
	// Wrapper function for glut SpecialKeyUp calls
	virtual void SpecialKeyUp(int  key, int  x, int  y) { };
	// Wrapper function for glut Motion calls
	virtual void Motion(int x, int y) { };
	// Wrapper function for glut Mouse calls
	virtual void Mouse(int button, int state, int x, int y) { };
	// Wrapper function for glut PassiveMotion calls
	virtual void PassiveMotion(int x, int y) { };
	// Wrapper function for glut Visibility calls
	virtual void Visibility(int v) { };
	// Wrapper function for glut Resize calls
	virtual void Resize(int w, int h) {
		windowWidth = w;
		windowHeight = h;

		glViewport(0, 0, windowWidth, windowHeight);
	};
	// Wrapper function for glut Timer calls
	virtual void Timer(int v) {
		timeForNextFrame = true;
	};
	// Initialize scene states such as polygon mode and culling direction, etc.
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

		// Enable lighting and texturing
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
	};
	// Clear the scene view
	void Clear() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	// Swap buffers safely
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
	// Set projection for the scene
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


