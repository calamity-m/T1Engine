#include "Collision.h"

float Collision::distance(vec3 p1, vec3 p2)
{
	

	float x = (p1.x - p2.x) * (p1.x - p2.x);
	float y = (p1.y - p2.y) * (p1.y - p2.y);
	float z = (p1.z - p2.z) * (p1.z - p2.z);

	if (x < 0) x *= -1;
	if (y < 0) x *= -1;
	if (z < 0) x *= -1;

	return sqrt(x+y+z);
}

bool Collision::checkCollisionVec3(vec3 v1, vec3 v2, float radius1, float radius2)
{
	float dist = distance(v1, v2);
	return (dist < (radius1 + radius2));
}

bool Collision::checkCollisionTransform(Transform t1, Transform t2, float radius1, float radius2)
{
	float dist = distance(t1.position, t2.position);
	return (dist < (radius1 + radius2));
}
