#ifndef skyrenderer_h
#define skyrenderer_h
#pragma once

#include "Transform.h"
#include "ResourceManager.h"
#include "Shapes.h"
#include "glut.h"

class SkyRenderer {

#define SKY_FRONT 0
#define SKY_LEFT 1
#define SKY_RIGHT 2
#define SKY_BACK 3
#define SKY_TOP 4
#define SKY_BOTTOM 5

public:

	enum SkyType { Sphere, Box };

	SkyRenderer();

	SkyRenderer(SkyType t);

	// Render Sky at given position
	void RenderAt(Transform pos, float size);

	// Render sky at origin
	void Render(int size);

	void setSkySphereTexture(int texId);

	void setSkyBoxTexture(int textures[6]);

	void setSkyType(SkyType t);

	int getSkyType();

	int getSkySphereTexture();

	int *getSkyBoxTexture();


protected:

	Transform transform;
	int skySphereTexture;
	int skyBoxTexture[6];
	GLUquadricObj *skySphereQuadric;
	SkyType type;

	void renderSkySphere(int sz);
	void renderSkyBox(float sz);
};

#endif // !skyrenderer_h


