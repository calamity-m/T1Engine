#ifndef terrainloader_h
#define terrainloader_h
#pragma once

//#include "fileOperations.h"
#include <stdlib.h>
#include "HeightField.h"
#include "Materials.h"
#include "glut.h"
#include "vec3.h"
#include "fileOperations.h"
#include <vector>

class TerrainLoader {

protected:

	void setMaterialHeight(Materials matLow, Materials matMid, Materials matHigh, float hL, float hM, float hH, float height);

public:
	
	struct Vec3_2 {
		vec3 n1;
		vec3 n2;

		Vec3_2() {

		};

		Vec3_2(vec3 a1, vec3 a2) {
			n1 = a1;
			n2 = a2;
		}
	};

	struct FaceNormals {
		vec3 n1;
		vec3 n2;
		vec3 n3;

		vec3 n11;
		vec3 n22;
		vec3 n33;

		FaceNormals() {

		};

		FaceNormals(vec3 a1, vec3 a2, vec3 a3, vec3 a11, vec3 a22, vec3 a33) {
			n1 = a1;
			n2 = a2;
			n3 = a3;

			n11 = a11;
			n22 = a22;
			n33 = a33;
		};
	};

	TerrainLoader();

	int loadTerrainSmoothed(char *fname, float scaleAmt, bool calcNormals, float heightHigh,
		float heightLow, float heightMid, Materials low, Materials mid, Materials high);

	int loadTerrain(char *fname, float scaleAmt, bool calcNormals, float heightHigh, 
		float heightLow, float heightMid, Materials low, Materials mid, Materials high);

};

#endif // !terrainloader_h


