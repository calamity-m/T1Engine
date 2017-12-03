#ifndef scenemuseum_h
#define scenemuseum_h
#pragma once

#include <stdlib.h>
#include "GlutScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Lights.h"
#include "Camera.h"
#include "vec3.h"
#include "fpscounter.h"
#include "ActorShip.h"
#include "ActorDisplay.h"
#include "ActorPlayer.h"
#include "ActorPortal.h"
#include "SkyRenderer.h"
#include "Collision.h"

/*
Parts are based of the following (full referencing provided in report)
https://www.gamedev.net/forums/topic/466416-glut-key-input-and-multiple-keys/
http://nghiaho.com/?p=1613
https://stackoverflow.com/questions/866679/using-opengl-glut-how-would-i-detect-if-two-keys-are-held-down-at-the-same-time

*/
class SceneMuseum : public GlutScene {

protected:

	void renderWorld();
	void renderGrid();
	void renderGround();
	void renderFog();
	void handlePlayerCollision();
	bool shiftmodifier = false;
	bool fps = false;
	bool keyboard[256];
	bool leftdown = false;
	bool rightdown = false;
	bool rotateModels = false;
	bool showPortal = false;
	bool fog = false;

	// Movement settings
	const float speed = 0.05;
	const float sensitivity = PI / 180 * 0.2;

public:

	Camera camera;

	ActorShip *baseShip;

	ActorPlayer *player;

	ActorDisplay *displayShip;
	ActorDisplay *ariShip;
	ActorDisplay *shuttleShip;
	ActorDisplay *puddleShip;

	ActorPortal *portal;

	Lights *light0;

	SkyRenderer skyBox;

	fpscounter fpsCounter;

	SceneMuseum();
	SceneMuseum(int w, int h);
	~SceneMuseum();

	void Render();
	void Update(void);
	void EnterScene();
	void ExitScene();
	void ASCII(unsigned char key, int x, int y);
	void ASCIIUp(unsigned char key, int x, int y);
	void SpecialKey(int key, int x, int y);
	void Mouse(int button, int state, int x, int y);
	void Motion(int x, int y);
	void PassiveMotion(int x, int y);
	void Timer(int v);

};

#endif // !scenemuseum_h


