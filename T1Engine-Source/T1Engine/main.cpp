/* Basic Cube Application */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "glut.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneDefault.h"
#include "SceneTerrain.h"
#include "SceneMuseum.h"
#include "SceneFly.h"

static int WindowWidth, WindowHeight;

static int AppMenu;

SceneManager *sceneManager;
SceneDefault *second;
SceneTerrain *third;
SceneMuseum *first;

void menuHandler(int item);

int main(int argc, char *argv[]) {

	// Initialize Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 75);
	glutCreateWindow("T1 Engine - Tests");

	// Initalize our resources
	ResourceManager::InitializeResources();
	Shapes::Initialize();

	// Load SceneManager
	sceneManager = new SceneManager(false, FPS, timerMSecs);

	// Load Scenes
	second = new SceneDefault(WindowWidth, WindowHeight);
	third = new SceneTerrain(WindowWidth, WindowHeight);
	first = new SceneMuseum(WindowWidth, WindowHeight);

	SceneManager::AddGlutScene(first);
	SceneManager::AddGlutScene(second);
	//SceneManager::AddGlutScene(second);
	SceneManager::AddGlutScene(third);

	SceneManager::SetGlutScene("Scene 1 -  World's Worst Museum", 0);

	SceneManager::BindSceneManager();

	// Initialize and Setup Menu
	AppMenu = glutCreateMenu(menuHandler);
	glutSetMenu(AppMenu);

	glutAddMenuEntry("Scene 1 - World's Worst Museum", menuScene1);
	glutAddMenuEntry("Scene 2 - World's Longest Stalemate", menuScene2);
	glutAddMenuEntry("Scene 3 - World's Most Interesting Terrain", menuScene3);
	glutAddMenuEntry("Exit", menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Start Glut Loop
	SceneManager::StartMainLoop();

	AppMenu = glutCreateMenu(menuHandler);
	glutSetMenu(AppMenu);

	glutAddMenuEntry("M1", menuScene1);
	glutAddMenuEntry("M2", menuScene2);
	glutAddMenuEntry("M3", menuScene3);
	glutAddMenuEntry("Exit", menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return 0;
}

/* Handle All Menu Inputs */
void menuHandler(int item) {
	switch (item) {
	case menuScene1:
		printf("Scene 1\n");
		SceneManager::SetGlutScene("Scene 1 - World's Worst Museum", 0);

		break;
	case menuScene2:
		printf("Scene 2\n");
		SceneManager::SetGlutScene("Scene 2 - World's Longest Stalemate", 1);

		break;
	case menuScene3:
		printf("Scene 3\n");
		SceneManager::SetGlutScene("Scene 3 - World's Most Interesting Terrain", 2);

		break;
	case menuExit:
		exit(5);
		break;
	}
}