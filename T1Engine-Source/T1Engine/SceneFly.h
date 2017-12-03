#ifndef scenefly_h
#define scenefly_h
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

class SceneFly : public GlutScene {

protected:

	void renderWorld();
	void renderGround();
	void fireBullet();
	void handlePlayerCollision();
	void handleBulletCollision();

	bool fps = false;
	bool keyboard[256];
	bool leftdown = false;
	bool rightdown = false;
	bool rotateModels = false;

	const float speed = 0.05;
	const float sensitivity = PI / 180 * 0.2;

public:

	Camera camera;

	ActorPlayer *player;

	std::vector<ActorDisplay*> targets;
	std::vector<ActorDisplay*> bullets;

	Lights *light0;

	SkyRenderer skyBox;

	fpscounter fpsCounter;

	SceneFly();
	SceneFly(int w, int h);
	~SceneFly();

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

#endif // !scenefly_h



