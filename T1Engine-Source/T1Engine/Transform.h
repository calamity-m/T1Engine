#ifndef transform_h
#define transform_h
#pragma once

#include "vec3.h"

class Transform {

public:
	
	vec3 position;
	vec3 rotation;
	vec3 scale;

	Transform() {
		scale.x = 1;
		scale.y = 1;
		scale.z = 1;
	}
};

#endif // !transform_h


