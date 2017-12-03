#include "Shapes.h"

static GLUquadric *cylQuadric;
static GLUquadric *diskQuadric;
static GLUquadric *coneQuadric;
static GLUquadric *sphereQuadric;

void Shapes::Initialize() {
	cylQuadric = gluNewQuadric();
	diskQuadric = gluNewQuadric();
	coneQuadric = gluNewQuadric();
	sphereQuadric = gluNewQuadric();
	gluQuadricTexture(cylQuadric, true);
	gluQuadricTexture(sphereQuadric, true);
	gluQuadricNormals(sphereQuadric, GL_SMOOTH);
	gluQuadricNormals(cylQuadric, GL_SMOOTH);
}

void Shapes::drawCube() {

}

void Shapes::drawCylinder(float radius, float height) {
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	gluCylinder(cylQuadric, radius, radius, height, 17, 4);
	glPopMatrix();
}

void Shapes::drawDisk(float innerRadius, float outerRadius) {
	glPushMatrix();
	gluDisk(diskQuadric, innerRadius, outerRadius, 17, 4);
	glPopMatrix();
}


void Shapes::drawCone(float baseRadius, float topRadius) {
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	gluCylinder(coneQuadric, baseRadius, topRadius, 1, 17, 4);
	glPopMatrix();
}

void Shapes::drawSphere(float radius, int slices, int stacks) {
	glPushMatrix();
	gluSphere(sphereQuadric, radius, slices, stacks);
	glPopMatrix();
}

void Shapes::drawWiredSphere(float radius, int slices, int stacks) {
	glPushMatrix();
	glutWireSphere(radius, slices, stacks);
	glPopMatrix();
}

