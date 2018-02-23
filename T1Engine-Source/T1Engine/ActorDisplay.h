#ifndef actordisplay_h
#define actordisplay_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

// Basic actor for displaying meshes and textures, has only simple circle collision and y axis rotation implemented ontop of base class
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

	// Should we light this actor
	bool lighting;
	// Should we be rotating
	bool rotate;
	// Should we draw our rotation
	bool drawCollision;
	// Collision radius used for collision checks between two actors
	float collisionRadius;

	// Basic constructor
	ActorDisplay(int modelIndex, int texIndex, float rotationAmt, float cRadius);
	// Initialize the display actor
	void Initialize();
	// Update display actor every frame
	void Update();
	// Rendercall for display actor
	void Render();
	// Return actor's rotation
	float GetRotation();
	// Return mesh's X Coord
	float GetModelX();
	// Return mesh's Y Coord
	float GetModelY();
	// Return mesh's Z Coord
	float GetModelZ();

};

#endif // !actordisplay_h
