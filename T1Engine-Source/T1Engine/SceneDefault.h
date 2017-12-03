#ifndef scenedefault_h
#define scenedefault_h
#pragma once

#include <stdlib.h>
#include "GlutScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Lights.h"
#include "ActorShip.h"
#include "ActorPlanet.h"
#include "ActorDisplay.h"
#include "Text2D.h"
#include "vec3.h"
#include "fpscounter.h"
#include "SkyRenderer.h"

class SceneDefault : public GlutScene {

protected:

	void RenderWorld();

public:
	
	vec3 lookAtVec, viewPoint, upVec;

	ActorShip *ship;
	ActorShip *ship2;

	ActorPlanet *planet;

	ActorDisplay *ariShip;

	Text2D *text2d;

	Lights *light0;

	fpscounter fps;

	SkyRenderer skyBox;

	float baseColour[3] = { 0, 1, 0 };
	bool showInstructions;

	float spinAngle;
	float wheelAngle;
	float fovAngle;

	SceneDefault();
	SceneDefault(int w, int h);
	~SceneDefault();

	void Render();
	void EnterScene();
	void ExitScene();
	void Update(void);
	void ASCII(unsigned char key, int x, int y);
	void SpecialKey(int key, int x, int y);
};

#endif // !scenedefault_h


