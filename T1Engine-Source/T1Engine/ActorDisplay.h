#ifndef actordisplay_h
#define actordisplay_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

class ActorDisplay : public Actor {

protected:

	/* Model data for our actor */
	ResourceManager::Model model;
	/* Integer ID for our main texture */
	int textureId;
	/* Rotation amount */
	float rotationAmount;
	/* Internal rotation of our actor along the Y Axis */
	float rotation;

public:

	bool lighting;
	bool rotate;
	bool drawCollision;
	float collisionRadius;

	ActorDisplay(int modelIndex, int texIndex, float rotationAmt, float cRadius);
	void Initialize();
	void Update();
	void Render();
	float GetRotation();
	float GetModelX();
	float GetModelY();
	float GetModelZ();

};

#endif // !actordisplay_h
