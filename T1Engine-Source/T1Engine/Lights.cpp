#include "Lights.h"

Lights::Lights() {

}

Lights::Lights(int lightId) {
	draw = true;
	drawLighting = true;
	setLightId(lightId);
	setRadius(1);
	setPos(1, 1, 0, 1);
	setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
	setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	setSpecular(1, 1, 1, 1);
	setGlobalAmbient(0.2f, 0.2f, 0.2f, 1.0f);
	setSpotLightDir(0, 0, 0);
	setSpotLightAngle(45);
	setType(normal);
	quadratic = gluNewQuadric();
}

Lights::~Lights() {
	delete quadratic;
}

void Lights::Update() {

}

void Lights::Render() {
	glPushMatrix();

	lightPos[0] = transform.position.x;
	lightPos[1] = transform.position.y;
	lightPos[2] = transform.position.z;

	glLightfv(lightId, GL_POSITION, lightPos);

	if (!draw)
		return;

	if (drawLighting) {
		if (glIsEnabled(GL_LIGHTING) == true)
			drawLighting = true;
		else
			drawLighting = false;
	}

	glDisable(GL_LIGHTING);

	// Do our translations and rotations
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);

	glutSolidSphere(drawRadius, 11, 11);

	if (drawLighting)
		glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Lights::enable() {
	glEnable(lightId);
	glLightfv(lightId, GL_POSITION, lightPos);
	glLightfv(lightId, GL_AMBIENT, lightAmb);
	glLightfv(lightId, GL_DIFFUSE, lightDiff);
	glLightfv(lightId, GL_SPECULAR, lightSpec);

	if (lightId == GL_LIGHT0)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

	if (type == spot) {
		glLightfv(lightId, GL_SPOT_DIRECTION, spotLightDir);
		glLightf(lightId, GL_SPOT_CUTOFF, spotLightAngle);
	}
	else {
		glLightf(lightId, GL_SPOT_CUTOFF, 180);
	}

	baseMaterial.setGlMaterial();
}

void Lights::disable() {
	glDisable(lightId);
}
void Lights::setRadius(float r) {
	drawRadius = r;
}

void Lights::setType(LightType t) {
	type = t;
}

void Lights::setLightId(int id) {
	lightId = id;
}

void Lights::setDiffuse(float r, float g, float b, float a) {
	lightDiff[0] = r;
	lightDiff[1] = g;
	lightDiff[2] = b;
	lightDiff[3] = a;
}

void Lights::setAmbient(float r, float g, float b, float a) {
	lightAmb[0] = r;
	lightAmb[1] = g;
	lightAmb[2] = b;
	lightAmb[3] = a;
}

void Lights::setGlobalAmbient(float r, float g, float b, float a) {
	globalAmbient[0] = r;
	globalAmbient[1] = g;
	globalAmbient[2] = b;
	globalAmbient[3] = a;
}

void Lights::setSpecular(float r, float g, float b, float a) {
	lightSpec[0] = r;
	lightSpec[1] = g;
	lightSpec[2] = b;
	lightSpec[3] = a;
}

void Lights::setSpotLightDir(float x, float y, float z) {
	spotLightDir[0] = x;
	spotLightDir[1] = y;
	spotLightDir[2] = z;
}

void Lights::setSpotLightAngle(float a) {
	spotLightAngle = a;
}

void Lights::setPos(float x, float y, float z, float w) {
	lightPos[0] = x;
	lightPos[1] = y;
	lightPos[2] = z;
	lightPos[3] = w;
	transform.position.x = x;
	transform.position.y = y;
	transform.position.z = z;
}

void Lights::setAttenuation(float a) {
	glLightf(lightId, GL_LINEAR_ATTENUATION, a);
}
