#ifndef scenemanager_h
#define scenemanager_h
#pragma once

#include "glut.h"
#include "GlutScene.h"
#include <vector>

class SceneManager {

protected:

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

	SceneManager(bool callGlutInit);
	SceneManager(bool callGlutInit, int fps, int msecs);
	~SceneManager();
	static void StartMainLoop();
	static void AddGlutScene(GlutScene *glutScene);
	static void SetGlutScene(char *title, int index);
	static void BindSceneManager();
	static int GetCurrentScene();
	static int GetSceneCount();
	

};

#endif // !scenemanager_h


