#ifndef actor_h
#define actor_h
#pragma once

#include "Transform.h"

class Actor {

public:
	bool active = true;
	Transform transform;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

#endif // !actor_h


