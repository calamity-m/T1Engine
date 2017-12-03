#ifndef terrain_h
#define terrain_h
#pragma once

#include "Transform.h"
#include "HeightField.h"
#include "Materials.h"
#include "ResourceManager.h"
#include "glut.h"
#include <vector>

class Terrain {

protected:

	ResourceManager::TerrainDEM dem;

public:

	Transform transform;

	Terrain();

	Terrain(ResourceManager::TerrainDEM dem);
	
	void Update();
	void Render();

};

#endif // !terrain_h

