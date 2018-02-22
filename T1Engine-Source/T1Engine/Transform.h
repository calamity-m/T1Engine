#ifndef transform_h
#define transform_h
#pragma once

#include "vec3.h"

/* Transform class for all actor objects, contains three vector3s for position, rotation and scale */
class Transform {

public:
	
	// Position of our transform
	vec3 position;
	// Rotation of our transform
	vec3 rotation;
	// Scale of our transform
	vec3 scale;

	// Basic constructor/initializor
	Transform() {
		scale.x = 1;
		scale.y = 1;
		scale.z = 1;
	}
};

#endif // !transform_h


