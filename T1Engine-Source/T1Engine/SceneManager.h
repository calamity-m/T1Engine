#ifndef scenemanager_h
#define scenemanager_h
#pragma once

#include "glut.h"
#include "GlutScene.h"
#include <vector>

/* Basic scene manager, works on a simple state machine where the wrapp function calls to the current scene */
class SceneManager {

protected:

	/* Below functions are simply wrappers for our SceneManager */
	static void WrapperRenderFunc(void);
	static void WrapperUpdateFunc(void);
	static void WrapperASCIIFunc(unsigned char key, int x, int y);
	static void WrapperASCIIUpFunc(unsigned char key, int x, int y);
	static void WrapperSpecialKeyFunc(int key, int x, int y);
	static void WrapperSpecialKeyUpFunc(int  key, int x, int y);
	static void WrapperMotionFunc(int x, int y);
	static void WrapperMouseFunc(int button, int state, int x, int y);
	static void WrapperPassiveMotionFunc(int x, int y);
	static void WrapperResizeFunc(int w, int h);
	static void WrapperVisibilityFunc(int v);
	static void WrapperTimerFunc(int value);

public:

	// Basic constructor, callGlutInit decides if we initialize glut (do not initialize glut twice)
	SceneManager(bool callGlutInit);
	// Similar constructor but allows for specification  of frame rate
	SceneManager(bool callGlutInit, int fps, int msecs);
	~SceneManager();
	// Lets start our main glut loop
	static void StartMainLoop();
	// Add a glut scene to our SceneManager
	static void AddGlutScene(GlutScene *glutScene);
	// Set the curreny glut scene in our SceneManager
	static void SetGlutScene(char *title, int index);
	// Bind all of our wrapper functions to glut calls
	static void BindSceneManager();
	// Return current scene id
	static int GetCurrentScene();
	// Return number of total scenes
	static int GetSceneCount();
	

};

#endif // !scenemanager_h


