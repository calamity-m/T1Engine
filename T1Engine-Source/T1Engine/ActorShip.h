#ifndef actorship_h
#define actorship_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

class ActorShip : public Actor {

protected:
	//bool active;
	ResourceManager::Model model;
	float sphereRot;
	float ringRot;

public:

	bool lighting;
	float collisionRadius;
	bool drawCollision;

	ActorShip(int modelIndex);
	void Initialize();
	void Update();
	void Render();
	void renderRotatingSpheres();
	void renderRotatingRings();
	void renderRotatingRing(float yval, float num, float rot);
	void renderPeg(float y);
};

#endif // !actorship_h

