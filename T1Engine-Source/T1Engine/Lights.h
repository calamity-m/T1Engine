#ifndef lights_h
#define lights_h
#pragma once

#include "Actor.h"
#include "ResourceManager.h"

class Lights : public Actor {

public:

	enum LightType {normal, spot};

	Materials baseMaterial;
	LightType type;
	GLUquadricObj *quadratic;

	float lightDiff[4];
	float lightAmb[4];
	float lightSpec[4];
	float lightPos[4];

	float globalAmbient[4];
	float spotLightDir[3];
	float spotLightAngle;

	int lightId;
	bool draw;
	bool drawLighting;
	float drawRadius;

	Lights();
	Lights(int lightId);
	~Lights();
	void Update();
	void Render();
	void setRadius(float r);
	void setType(LightType t);
	// GL_LIGHT0 or GL_LIGHT1 etc.
	void setLightId(int id);
	void setDiffuse(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setGlobalAmbient(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setSpotLightDir(float x, float y, float z);
	void setSpotLightAngle(float a);
	void setPos(float x, float y, float z, float w);
	void setAttenuation(float a);
	void enable();
	void disable();

};

#endif // !lights_h


