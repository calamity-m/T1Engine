#include "ResourceManager.h"

static char *windowName;
static std::vector<ResourceManager::Texture> texList;
static std::vector<ResourceManager::Model> modelList;
static std::vector<ResourceManager::TerrainDEM> terrains;
static MeshLoader *loader;
static TerrainLoader *terrainLoader;
static std::vector<Materials> materials;
static std::vector<HeightField> heightFields;

void ResourceManager::InitializeResources() {
	// Load Models
	ResourceManager::addModel("Resources\\Meshes\\LuminarisOBJTriangulated.obj", "Ship");
	ResourceManager::addModel("Resources\\Meshes\\AriOBJ.obj", "Ship2");
	ResourceManager::addModel("Resources\\Meshes\\PuddleJumperOBJ.obj", "Trex");
	ResourceManager::addModel("Resources\\Meshes\\ShuttleOBJ.obj", "Bronto");
	ResourceManager::addModel("Resources\\Meshes\\StarGateOBJ.obj", "StarGate");

	// Load Textures
	ResourceManager::addTexture("Resources\\Textures\\shiptexture.bmp", "shipname", true);
	ResourceManager::addTexture("Resources\\Textures\\venustexture.bmp", "venus", true);
	ResourceManager::addTexture("Resources\\Textures\\smudgetexture.bmp", "smudge", true);
	ResourceManager::addTexture("Resources\\Textures\\grassTexture.bmp", "moss", true);
	ResourceManager::addTexture("Resources\\Textures\\metalTextureHalf.bmp", "metal", true);
	ResourceManager::addTexture("Resources\\Textures\\ariTexture.bmp", "ari", true);
	ResourceManager::addTexture("Resources\\Textures\\puddleJumperTexture.bmp", "puddle", true);

	// Load Skybox Textures
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_front.bmp", "skyfront", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_left.bmp", "skyleft", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_right.bmp", "skyright", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_back.bmp", "skyback", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_up.bmp", "skytop", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\Scifi\\sky_down.bmp", "skyback", false);

	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_front.bmp", "skyfront", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_left.bmp", "skyleft", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_right.bmp", "skyright", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_back.bmp", "skyback", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_up.bmp", "skytop", false);
	ResourceManager::addTexture("Resources\\Textures\\Sky\\StarsHQ\\sky_down.bmp", "skyback", false);

	ResourceManager::addTexture("Resources\\Textures\\eventhorizonTexture.bmp", "eventhorizon", true);

	// Load Materials
	ResourceManager::addMaterial(Materials());
	ResourceManager::addMaterial(Materials(Materials::Snow));
	ResourceManager::addMaterial(Materials(Materials::Grass));
	ResourceManager::addMaterial(Materials(Materials::Sand));

	// Load Terrains
	ResourceManager::addTerrain("Resources\\Terrains\\X20_23.txt", "Terrain 1", 0.005, true,
		5, 0, 0.2, ResourceManager::getMaterial(3), ResourceManager::getMaterial(2), ResourceManager::getMaterial(1));
}

unsigned int ResourceManager::addModel(char *fname, char *modelName) {

	modelList.push_back(ResourceManager::Model(loader->loadTexturedMeshes(fname), modelName));

	return 1;
}

unsigned int ResourceManager::addTexture(char *fname, char *textureName, bool mipmap) {
	// Initialize our texture
	texList.push_back(Texture());

	// Set our texture handle
	glGenTextures(1, &texList[texList.size() - 1].texHandle);

	// Please work m8
	CBitmap bmpData(fname);

	glBindTexture(GL_TEXTURE_2D, texList[texList.size() - 1].texHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	if (mipmap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		int rtn = gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			GL_RGBA,
			bmpData.GetWidth(),
			bmpData.GetHeight(),
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bmpData.GetBits()
		);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			3,
			bmpData.GetWidth(),
			bmpData.GetHeight(),
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			bmpData.GetBits()
		);
	}

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	return 0;
}

ResourceManager::Model ResourceManager::getModel(char *name) {
	return modelList[0];
}

ResourceManager::Model ResourceManager::getModel(int index) {
	if ((size_t)index >= modelList.size())
		return modelList[0];

	return modelList[index];
}

ResourceManager::Texture ResourceManager::getTexture(char *name) {
	return texList[0];
}

GLuint ResourceManager::getTexture(int index) {
	if ((size_t)index >= texList.size())
		return -1;

	return texList[index].texHandle;
}

unsigned int ResourceManager::addMaterial(Materials m) {
	materials.push_back(m);

	return 1;
}

Materials ResourceManager::getMaterial(int index) {
	if ((size_t)index >= materials.size())
		return Materials();

	return materials[index];
}

void ResourceManager::applyMaterial(int index) {
	if (index >= materials.size()) {
		Materials m;
		m.setGlMaterial();
		return;
	}

	materials[index].setGlMaterial();
}

unsigned int ResourceManager::addHeightField(char * fname, float scaleAmt) {
	
	int map[MAXWIDTH][MAXDEPTH];
	float mapScaled[MAXWIDTH][MAXDEPTH];
	int mapWidth;
	int mapHeight;
	
	readHeightField(fname, &mapWidth, &mapHeight, map);
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			mapScaled[i][j] = (float)map[i][j] * scaleAmt;
		}
	}

	heightFields.push_back(HeightField(mapWidth, mapHeight, mapScaled));
	
	return 1;
}

HeightField ResourceManager::getHeightField(int index) {
	if ((size_t)index >= heightFields.size())
		return HeightField();

	return heightFields[index];
}

unsigned int ResourceManager::addTerrain(char * fname, char *name, float scaleAmt, bool calcNormals, float heightHigh, 
	float heightLow, float heightMid, Materials low, Materials mid, Materials high) {
			
	terrains.push_back(ResourceManager::TerrainDEM(
		terrainLoader->loadTerrain(fname, scaleAmt, calcNormals,
		heightHigh, heightLow, heightMid, low, mid, high), name));


	return 1;
}

unsigned int ResourceManager::addTerrainFookOff(char * fname, char *name, float scaleAmt, bool calcNormals, float heightHigh,
	float heightLow, float heightMid, Materials low, Materials mid, Materials high) {

	terrains.push_back(ResourceManager::TerrainDEM(
		terrainLoader->loadTerrainSmoothed(fname, scaleAmt, calcNormals,
			heightHigh, heightLow, heightMid, low, mid, high), name));

	return 1;

}


ResourceManager::TerrainDEM ResourceManager::getTerrain(int index) {
	if (index >= terrains.size())
		return TerrainDEM();

	return terrains[index];
}

void ResourceManager::setWindowName(char *name) {
	windowName = name;
}

char * ResourceManager::getWindowName() {
	return windowName;
}

int ResourceManager::getNoOfTextures() {
	return texList.size();
}

int ResourceManager::getNoOfModels() {
	return modelList.size();
}

void ResourceManager::clear() {
	modelList.clear();
	texList.clear();
}
