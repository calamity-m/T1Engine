#ifndef heightfield_h
#define heightfield_h
#pragma once

#define MAXWIDTH 257
#define MAXDEPTH 257

class HeightField {

public:

	float map[MAXWIDTH][MAXDEPTH];
	int xSteps;
	int zSteps;

	HeightField() {
		xSteps = 0;
		zSteps = 0;
		for (int i = 0; i < MAXDEPTH; i++) {
			map[i][i] = i;
		}
	}

	HeightField(int xstep, int zstep) {
		xSteps = xstep;
		zSteps = zstep;
		for (int i = 0; i < MAXDEPTH; i++) {
			map[i][i] = i;
		}
	};

	HeightField(int xstep, int zstep, float m[MAXWIDTH][MAXDEPTH]) {
		xSteps = xstep;
		zSteps = zstep;
		for (int i = 0; i < MAXWIDTH; i++) {
			for (int j = 0; j < MAXDEPTH; j++) {
				map[i][j] = m[i][j];
			}
		}
	};

	void init(int xstep, int zstep, float m[MAXWIDTH][MAXDEPTH]) {
		xSteps = xstep;
		zSteps = zstep;
		for (int i = 0; i < MAXWIDTH; i++) {
			for (int j = 0; j < MAXDEPTH; j++) {
				map[i][j] = m[i][j];
			}
		}
	}

};


#endif // !heightfield_h


