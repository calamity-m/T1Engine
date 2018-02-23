#ifndef actorship_h
#define actorship_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

// Basic ship class
class ActorShip : public Actor {

protected:
	// bool active;
	ResourceManager::Model model;
	// Internal rotation of our ship's spheres
	float sphereRot;
	// Internal rotation of our ship's rings
	float ringRot;

public:

	// Should we light this actor?
	bool lighting;
	// Collision sphere radius
	float collisionRadius;
	// Should we draw our collision sphere?
	bool drawCollision;

	ActorShip(int modelIndex);
	void Initialize();
	void Update();
	void Render();
	// Render ship's spheres
	void renderRotatingSpheres();
	// Render ship's rotating rings
	void renderRotatingRings();
	// Render a single rotating ring
	void renderRotatingRing(float yval, float num, float rot);
	// Render a single peg to be used in a rotating ring
	void renderPeg(float y);
};

#endif // !actorship_h

