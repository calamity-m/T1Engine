#ifndef actorplanet_h
#define actorplanet_h
#pragma once

#include "Actor.h"
#include "Shapes.h"

class ActorPlanet : public Actor {

public:
	enum Type { Venus, Moon, Other };

	ActorPlanet(float rotRate, float r, Type planetType);
	void Initialize();
	void Update();
	void Render();
	void setType(Type planetType);

protected:
	//bool active;
	float planetRot;
	float rotationRate;
	float radius;
	Type type;
};


#endif // !actorplanet_h


