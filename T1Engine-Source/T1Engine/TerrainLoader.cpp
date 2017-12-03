#include "TerrainLoader.h"

TerrainLoader::TerrainLoader() {

}

int TerrainLoader::loadTerrainSmoothed(char * fname, float scaleAmt, bool calcNormals, float heightHigh, float heightLow, float heightMid, Materials low, Materials mid, Materials high) {

	return loadTerrain(fname, scaleAmt, calcNormals, heightHigh,
		heightLow, heightMid, low, mid, high);
}

int TerrainLoader::loadTerrain(char *fname, float scaleAmt, bool calcNormals, float heightHigh,
	float heightLow, float heightMid, Materials low, Materials mid, Materials high) {

	int map[MAXWIDTH][MAXDEPTH];
	float mapScaled[MAXWIDTH][MAXDEPTH];
	int mapWidth;
	int mapHeight;

	std::vector<vec3> normals;

	readHeightField(fname, &mapWidth, &mapHeight, map);
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			mapScaled[i][j] = (float)map[i][j] * scaleAmt;
		}
	}

	HeightField heightField = HeightField(mapWidth, mapHeight, mapScaled);
	
	int xsteps = heightField.xSteps;
	float xsize = (float)xsteps;

	int zsteps = heightField.zSteps;
	float zsize = (float)zsteps;

	GLfloat xdelta = xsize / xsteps;
	GLfloat zdelta = zsize / zsteps;

	if (calcNormals) {
		// First Smooth pass
		for (int x = 0; x < xsteps - 1; x++) {
			for (int z = 0; z < zsteps - 1; z++) {
				// First Triangle
				vec3 normal = polygonNormal(normal, vec3(xdelta*x, 0.01 + heightField.map[x][z + 1], zdelta*z + zdelta),
					vec3(xdelta*x + xdelta, 0.01 + heightField.map[x + 1][z], zdelta*z),
					vec3(xdelta*x, 0.01 + heightField.map[x][z], zdelta*z));

				normals.push_back(normal);

				// Second Triangle
				vec3 normal2 = polygonNormal(normal2, vec3(xdelta*x + xdelta, 0.01 + heightField.map[x + 1][z], zdelta*z),
					vec3(xdelta*x, 0.01 + heightField.map[x][z + 1], zdelta*z + zdelta),
					vec3(xdelta*x + xdelta, 0.01 + heightField.map[x + 1][z + 1], zdelta*z + zdelta));

				normals.push_back(normal2);
			}
		}


	}

	int x = glGenLists(1);

	glNewList(x, GL_COMPILE);

	int triangleCount = 0;

	glBegin(GL_TRIANGLES);

	for (int x = 0; x < xsteps - 1; x++) {
		for (int z = 0; z < zsteps - 1; z++) {
			if (calcNormals)
				glNormal3f(normals[triangleCount].x, normals[triangleCount].y, normals[triangleCount].z);

			triangleCount++;

			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x][z + 1]);
			glTexCoord2f(0, 0);
			glVertex3f(xdelta*x, heightField.map[x][z + 1], zdelta*z + zdelta);

			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x + 1][z]);
			glTexCoord2f(3, 0);
			glVertex3f(xdelta*x + xdelta, heightField.map[x + 1][z], zdelta*z);

			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x][z]);
			glTexCoord2f(3, 3);
			glVertex3f(xdelta*x, heightField.map[x][z], zdelta*z);

			if (calcNormals)
				glNormal3f(normals[triangleCount].x, normals[triangleCount].y, normals[triangleCount].z);

			triangleCount++;


			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x + 1][z]);
			glTexCoord2f(3, 3);
			glVertex3f(xdelta*x + xdelta, heightField.map[x + 1][z], zdelta*z);

			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x][z + 1]);
			glTexCoord2f(0, 3);
			glVertex3f(xdelta*x, heightField.map[x][z + 1], zdelta*z + zdelta);

			setMaterialHeight(low, mid, high, heightLow, heightMid, heightHigh, heightField.map[x + 1][z + 1]);
			glTexCoord2f(0, 0);
			glVertex3f(xdelta*x + xdelta, heightField.map[x + 1][z + 1], zdelta*z + zdelta);
		}
	}

	glEnd();

	glEndList();
	

	return x;
}

void TerrainLoader::setMaterialHeight(Materials matLow, Materials matMid, Materials matHigh, float hL, float hM, float hH, float height) {
	if (height >= hH)
		matHigh.setGlMaterial();
	else if (height >= hM)
		matMid.setGlMaterial();
	else
		matLow.setGlMaterial();
}

