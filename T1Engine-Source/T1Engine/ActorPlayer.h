#ifndef actorplayer_h
#define actorplayer_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

class ActorPlayer : public Actor {

protected:

	float health;

public:

	Transform prevTransform;
	float collisionRadius;
	bool drawCollision;
	bool drawShip;

	ActorPlayer();
	ActorPlayer(Transform initialPos);
	void Initialize();
	void Update();
	void Render();
	void MovePlayer(Transform t);

};

#endif // !actorplayer_h


