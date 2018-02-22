#ifndef actor_h
#define actor_h
#pragma once

#include "Transform.h"

/* Base class for any scene objects that have a transform */
class Actor {

public:
	// Is this actor currently active?
	bool active = true;
	// Transform of this actor
	Transform transform;
	// Update called each frame
	virtual void Update() = 0;
	// Render call
	virtual void Render() = 0;
};

#endif // !actor_h


