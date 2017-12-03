#ifndef resourcemanager_h
#define resourcemanager_h
#pragma once

#include <math.h>
#include "MeshLoader.h"
#include "TerrainLoader.h"
#include "Materials.h"
#include "HeightField.h"
#include "fileOperations.h"
#include "bitmap.h"


// Near and Far planes for rendering
#define NEARPLANE 0.5
#define FARPLANE 120.0

// Escape ASCII Key
#define ESC 27

// Menu values
#define menuScene2 1
#define menuScene1 2
#define menuScene3 3
#define menuScene4 4
#define menuExit 99

#define GL_CLAMP_TO_EDGE 0x812F

#define FPS 60
#define timerMSecs ((int)1000/FPS)

#define PI 3.14159265358979323846264338327950288

class ResourceManager {

public:

	struct Texture {
		GLuint texHandle;
		char *texName;

		Texture() {

		}
	};

	struct Model {
		std::vector<MeshLoader::Mesh> meshData;
		char *modelName;
		GLuint modelId;

		Model() {
			modelId = -1;
		}

		Model(std::vector<MeshLoader::Mesh> data, char *name) {
			meshData = data;
			modelName = name;
		}
	};

	struct TerrainDEM {
		int terrain;
		char *terrainName;

		TerrainDEM() {

		}

		TerrainDEM(int data, char *name) {
			terrain = data;
			terrainName = name;
		}

		void Render() {
			glPushMatrix();
			glCallList(terrain);
			glPopMatrix();
		}
	};

	// Can be used to initialize any resources needed via the resource manager.
	static void InitializeResources();

	// Loads a model into the modellist vector
	// Returns 0 on fail or 1 on success
	static unsigned int addModel(char *fname, char *modelName);

	// Returns model with given name
	// Slower and more taxing on cpu, does name comp.
	static Model getModel(char *name);

	// Returns model of given index
	// Faster than searching with name
	static Model getModel(int index);

	// Loads a texture into the texlist vector
	// Returns 0 on fail or 1 on success
	static unsigned int addTexture(char *fname, char *textureName, bool mipmap);

	// Returns texture with given name
	static Texture getTexture(char *name);

	// Returns texture of given index
	static GLuint getTexture(int index);

	// Adds a material into the materials vector
	static unsigned int addMaterial(Materials m);

	// Returns material of given index
	static Materials getMaterial(int index);

	// Applies selected material to Opengl
	static void applyMaterial(int index);

	// Loads a height field into the heightFields vector
	static unsigned int addHeightField(char *fname, float scaleAmt);

	// Returns a heightfield of given index
	static HeightField getHeightField(int index);

	// Loads a terrain into the terrains vector
	static unsigned int addTerrain(char *fname, char *name, float scaleAmt, bool calcNormals, float heightHigh,
		float heightLow, float heightMid, Materials low, Materials mid, Materials high);

	// Not implemented yet
	static unsigned int addTerrainFookOff(char * fname, char * name, float scaleAmt, bool calcNormals, float heightHigh, 
		float heightLow, float heightMid, Materials low, Materials mid, Materials high);

	// Returns a terrain of given index
	static TerrainDEM getTerrain(int index);

	// Sets window name
	static void setWindowName(char *name);

	// Returns window name
	static char* getWindowName();

	// Return number of textures currently loaded
	static int getNoOfTextures();

	// Return number of models current loaded
	static int getNoOfModels();

	// Clear tex and model lists
	static void clear();
};

#endif // !resourcemanager_h