#include <stdlib.h>
#include "SceneManager.h"

static int currScene;
static std::vector<GlutScene*> glutScenes;
static int FPS;
static int timerMSecs;

SceneManager::SceneManager(bool CallGlutInit) {
	SceneManager(CallGlutInit, 60, ((int)1000 / 60));
}

SceneManager::SceneManager(bool CallGlutInit, int fps, int msecs) {

	FPS = fps;
	timerMSecs = msecs;

	// Dummy vars
	if (CallGlutInit) {
		char * dummy_argv[1];
		dummy_argv[0] = "run";
		int dummy_argc = 1;
		glutInit(&dummy_argc, dummy_argv);
	}
}

SceneManager::~SceneManager() {

}

void SceneManager::StartMainLoop() {
	glutMainLoop();
}

void SceneManager::BindSceneManager() {
	glutDisplayFunc(WrapperRenderFunc);
	glutIdleFunc(WrapperUpdateFunc);
	glutKeyboardFunc(WrapperASCIIFunc);
	glutKeyboardUpFunc(WrapperASCIIUpFunc);
	glutSpecialFunc(WrapperSpecialKeyFunc);
	glutSpecialUpFunc(WrapperSpecialKeyUpFunc);
	glutMotionFunc(WrapperMotionFunc);
	glutMouseFunc(WrapperMouseFunc);
	glutPassiveMotionFunc(WrapperPassiveMotionFunc);
	glutReshapeFunc(WrapperResizeFunc);
	glutVisibilityFunc(WrapperVisibilityFunc);
	glutTimerFunc(timerMSecs, WrapperTimerFunc, 0);
}

void SceneManager::SetGlutScene(char *title, int index) {
	glutSetWindowTitle(title);
	glutScenes[currScene]->ExitScene();
	glutScenes[index]->EnterScene();
	currScene = index;

}

void SceneManager::AddGlutScene(GlutScene *glutScene) {
	glutScenes.push_back(glutScene);
}

int SceneManager::GetCurrentScene() {
	return currScene;
}

int SceneManager::GetSceneCount() {
	return glutScenes.size();
}

void SceneManager::WrapperRenderFunc(void) {
	glutScenes[GetCurrentScene()]->Render();
}

void SceneManager::WrapperUpdateFunc(void) {
	glutScenes[GetCurrentScene()]->Update();
}

void SceneManager::WrapperASCIIFunc(unsigned char key, int x, int y) {
	glutScenes[GetCurrentScene()]->ASCII(key, x, y);
}

void SceneManager::WrapperASCIIUpFunc(unsigned char key, int x, int y) {
	glutScenes[GetCurrentScene()]->ASCIIUp(key, x, y);
}

void SceneManager::WrapperSpecialKeyFunc(int key, int x, int y) {
	glutScenes[GetCurrentScene()]->SpecialKey(key, x, y);
}

void SceneManager::WrapperSpecialKeyUpFunc(int key, int x, int y) {
	glutScenes[GetCurrentScene()]->SpecialKeyUp(key, x, y);
}

void SceneManager::WrapperMotionFunc(int  x, int y) {
	glutScenes[GetCurrentScene()]->Motion(x, y);
}

void SceneManager::WrapperMouseFunc(int button, int state, int x, int y) {
	glutScenes[GetCurrentScene()]->Mouse(button, state, x, y);
}

void SceneManager::WrapperPassiveMotionFunc(int x, int y) {
	glutScenes[GetCurrentScene()]->PassiveMotion(x, y);
}

void SceneManager::WrapperResizeFunc(int w, int h) {
	glutScenes[GetCurrentScene()]->Resize(w, h);
}

void SceneManager::WrapperVisibilityFunc(int v) {
	glutScenes[GetCurrentScene()]->Visibility(v);
}

void SceneManager::WrapperTimerFunc(int value)
{
	glutScenes[GetCurrentScene()]->Timer(value);
	glutTimerFunc(timerMSecs, WrapperTimerFunc, 0);
}