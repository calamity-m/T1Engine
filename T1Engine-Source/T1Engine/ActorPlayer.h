#ifndef actorplayer_h
#define actorplayer_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

// Basic class for player actor
class ActorPlayer : public Actor {

protected:

	// Internal health
	float health;

public:

	// Previous Transform
	Transform prevTransform;
	// Current Collision radius
	float collisionRadius;
	// Should we draw our collision sphere?
	bool drawCollision;
	// Should we draw our mesh/model?
	bool drawShip;

	// Basic constructor
	ActorPlayer();
	// Basic constructor, initializes players transform to initialPos
	ActorPlayer(Transform initialPos);
	// Initialize this player actor
	void Initialize();
	// Update this player actor
	void Update();
	// Rendercall for this player actor
	void Render();
	// Move player to given transform t
	void MovePlayer(Transform t);

};

#endif // !actorplayer_h


