#ifndef material_h
#define material_h
#pragma once

class Materials {

protected:
	float diffuse[4];
	float ambient[4];
	float specular[4];
	float emissive[4];
	int shiny;

public:
	
	enum default{Snow, Sand, Grass};

	Materials();
	Materials(default type);

	void setDiffuse(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmissive(float r, float g, float b, float a);
	void setShiny(float s);
	void setShiny(int s);
	void setGlMaterial();
	void setWhiteRubber();
	void setSnow();
	void setGrass();
	void setSand();
	
};


#endif // !material_h


