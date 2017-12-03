#include "Materials.h"
#include "glut.h"

Materials::Materials() {
	setWhiteRubber();
}

Materials::Materials(default type) {
	if (type == Snow)
		setSnow();
	else if (type == Sand)
		setSand();
	else if (type == Grass)
		setGrass();
}

void Materials::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
};
void Materials::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
};
void Materials::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
};
void Materials::setEmissive(float r, float g, float b, float a) {
	emissive[0] = r;
	emissive[1] = g;
	emissive[2] = b;
	emissive[3] = a;
};
void Materials::setShiny(float s) {
	shiny = (int)s * 128;
}
void Materials::setShiny(int s) {
	shiny = s;
}
void Materials::setGlMaterial() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissive);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

void Materials::setWhiteRubber() {
	setAmbient(0.05, 0.05, 0.05, 1);
	setDiffuse(0.5, 0.5, 0.5, 1);
	setSpecular(0.7, 0.7, 0.7, 1);
	setEmissive(0, 0, 0, 0);
	setShiny(12);
}

void Materials::setSnow() {
	setAmbient(0.7f, 0.7f, 0.7f, 1);
	setDiffuse(0.9f, 0.9f, 0.9f, 1);
	setSpecular(0.6f, 0.6f, 0.6f, 1);
	setEmissive(0, 0, 0, 0);
	setShiny(12);
}

void Materials::setGrass() {
	setAmbient(0.13f, 0.25f, 0.15f, 1);
	setDiffuse(0.24f, 0.89f, 0.33f, 1);
	setSpecular(0.116228f, 0.316228f, 0.116228f, 1);
	setEmissive(0, 0, 0, 0);
	setShiny((int)(0.1*128.0));
}

void Materials::setSand() {
	setAmbient(0.4f, 0.4f, 0.1575f, 1);
	setDiffuse(0.7f, 0.7f, 0.2f, 1);
	setSpecular(0.316228f, 0.316228f, 0.216228f, 1);
	setEmissive(0, 0, 0, 0);
	setShiny((int)(0.1*128.0));
}
