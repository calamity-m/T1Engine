#ifndef shapes_h
#define shapes_h
#pragma once

#include "ResourceManager.h"

class Shapes {

public:

	static void Initialize();
	static void drawCube();
	static void drawCylinder(float radius, float height);
	static void drawDisk(float innerRadius, float outerRadius);
	static void drawCone(float baseRadius, float topRadius);
	static void drawSphere(float radius, int slices, int stacks);
	static void drawWiredSphere(float radius, int slices, int stacks);
};

#endif // !shapes_h


