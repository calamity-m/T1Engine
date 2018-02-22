#ifndef collision_h
#define collision_h
#pragma once

#include <cmath>
#include "Transform.h"

/* Base class for collisions, only implements simple circle-circle collisions at this moment */
class Collision {

protected:

	// Check the distance between two vector3 points
	static float distance(vec3 p1, vec3 p2);

public:

	// Check for collision between two vectors and two radi
	static bool checkCollisionVec3(vec3 v1, vec3 v2, float radius1, float radius2);
	// Check for collision between two transforms and two radi
	static bool checkCollisionTransform(Transform t1, Transform t2, float radius1, float radius2);

};

#endif // !collision_h


