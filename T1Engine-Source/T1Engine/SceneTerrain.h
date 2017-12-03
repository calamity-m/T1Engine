#ifndef sceneterrain_h
#define sceneterrain_h
#pragma once

#include <stdlib.h>
#include "GlutScene.h"
#include "SceneManager.h"
#include "Lights.h"
#include "Text2D.h"
#include "vec3.h"
#include "fpscounter.h"
#include "Terrain.h"
#include "SkyRenderer.h"

class SceneTerrain : public GlutScene {

protected:

	void RenderWorld();

public:

	vec3 lookAtVec, viewPoint, upVec;

	Text2D *text2d;

	Lights *light0;

	Terrain ter;

	fpscounter fps;

	Materials rtn;

	SkyRenderer skyBox;

	float baseColour[3] = { 0, 1, 0 };
	bool showInstructions;
	bool showTexturing;
	bool showWireframe;

	float spinAngle;
	float wheelAngle;
	float fovAngle;

	SceneTerrain();
	SceneTerrain(int w, int h);
	~SceneTerrain();

	void Render();
	void Update(void);
	void EnterScene();
	void ExitScene();
	void ASCII(unsigned char key, int x, int y);
	void SpecialKey(int key, int x, int y);
};

#endif // !scenedefault_h


