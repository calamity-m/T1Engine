#ifndef actorportal_h
#define actorportal_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

// Unfinished portal class, meant  to teleport player to next level on collision
class ActorPortal : public Actor {

protected:

	// Model
	ResourceManager::Model model;

public:

	// Should we light our portal?
	bool lighting;
	// Collision sphere radius - needs to be changed and have AABB implemented
	float collisionRadius;
	// Should we draw our collision sphere?
	bool drawCollision;

	// Basic constructor
	ActorPortal(int modelIndex);
	// Initialize our portal
	void Initialize();
	// Update our portal every frame
	void Update();
	// Rendercall for our  portal
	void Render();

};

#endif // !actorportal_h


