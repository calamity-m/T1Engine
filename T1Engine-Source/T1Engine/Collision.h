#ifndef collision_h
#define collision_h
#pragma once

#include <cmath>
#include "Transform.h"

class Collision {

protected:

	static float distance(vec3 p1, vec3 p2);

public:

	static bool checkCollisionVec3(vec3 v1, vec3 v2, float radius1, float radius2);
	static bool checkCollisionTransform(Transform t1, Transform t2, float radius1, float radius2);

};

#endif // !collision_h


