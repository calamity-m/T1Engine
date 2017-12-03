#ifndef actorportal_h
#define actorportal_h
#pragma once

#include "Actor.h"
#include "Shapes.h"
#include "ResourceManager.h"

class ActorPortal : public Actor {

protected:

	ResourceManager::Model model;

public:

	bool lighting;
	float collisionRadius;
	bool drawCollision;

	ActorPortal(int modelIndex);
	void Initialize();
	void Update();
	void Render();

};

#endif // !actorportal_h


