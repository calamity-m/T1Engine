#ifndef actorplanet_h
#define actorplanet_h
#pragma once

#include "Actor.h"
#include "Shapes.h"

// Very basic actor for a simple planet object
class ActorPlanet : public Actor {

public:
	// Planet types
	enum Type { Venus, Moon, Other };

	// Basic constructor
	ActorPlanet(float rotRate, float r, Type planetType);
	// Initialize our actor
	void Initialize();
	// Update this actor
	void Update();
	// Rendercall for this actor
	void Render();
	// Set the planet's type for planetType
	void setType(Type planetType);

protected:
	// bool active;
	float planetRot;
	// Rate of rotation every frame
	float rotationRate;
	// Radius of planet
	float radius;
	// Type of planet
	Type type;
};


#endif // !actorplanet_h


