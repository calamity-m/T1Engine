#include "SkyRenderer.h"

SkyRenderer::SkyRenderer() {
	type = Box;
	skySphereQuadric = gluNewQuadric();
	gluQuadricTexture(skySphereQuadric, true);
	gluQuadricNormals(skySphereQuadric, GL_SMOOTH);
	gluQuadricOrientation(skySphereQuadric, GLU_INSIDE);
}

SkyRenderer::SkyRenderer(SkyType t) {
	type = t;
	skySphereQuadric = gluNewQuadric();
}

void SkyRenderer::RenderAt(Transform pos, float size) {
	transform = pos;
	glPushMatrix();
	if (type == Sphere)
		renderSkySphere(size);
	else
		renderSkyBox(size);
	glPopMatrix();
}

void SkyRenderer::Render(int size) {
	transform.position = vec3(0, 0, 0);
	glPushMatrix();
	if (type == Sphere)
		renderSkySphere(size);
	else
		renderSkyBox(size);
	glPopMatrix();

}


void SkyRenderer::renderSkySphere(int sz) {
	bool wasLighting;

	wasLighting = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(0);

	glDisable(GL_CULL_FACE);

	glColor3f(1, 1, 1);

	glTranslatef(transform.position.x, transform.position.y, transform.position.z);

	glRotatef(270, 1, 0, 0);

	// Render Sky Sphere
	glBindTexture(GL_TEXTURE_2D, skySphereTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//glScalef(sz, sz, sz);

	Shapes::drawSphere(sz, 75, 75);

	glDepthMask(1);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	if (wasLighting)
		glEnable(GL_LIGHTING);

}

void SkyRenderer::renderSkyBox(float sz) {
	bool wasLighting;

	wasLighting = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(0);
	glColor3f(1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_FRONT]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Render Sky Box
	glBegin(GL_QUADS);
	// Front
	//glTexCoord2f(0.0f, 1.0f);
	glTexCoord2f(0, 0);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	//glTexCoord2f(1.0f, 1.0f);
	glTexCoord2f(1, 0);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	//glTexCoord2f(1.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	//glTexCoord2f(0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_LEFT]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// Left
	glTexCoord2f(0, 0);
	//glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_LEFT]);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 0);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(1, 1);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(0, 1);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_RIGHT]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// Right
	glTexCoord2f(0, 0);
	//glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_RIGHT]);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(1, 0);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 1);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(0, 1);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_BACK]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// Back
	glTexCoord2f(0, 0);
	//glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_BACK]);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 0);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 1);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(0, 1);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_TOP]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// Upper
	glTexCoord2f(0, 0);
	//glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_TOP]);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(1, 0);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(1, 1);
	glVertex3f(sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(0, 1);
	glVertex3f(-sz + transform.position.x, sz + transform.position.y, sz + transform.position.z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_BOTTOM]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBegin(GL_QUADS);
	// Lower
	glTexCoord2f(0, 0);
	//glBindTexture(GL_TEXTURE_2D, skyBoxTexture[SKY_BOTTOM]);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 0);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, sz + transform.position.z);
	glTexCoord2f(1, 1);
	glVertex3f(sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	glTexCoord2f(0, 1);
	glVertex3f(-sz + transform.position.x, -sz + transform.position.y, -sz + transform.position.z);
	glEnd();

	//glCullFace(GL_BACK);

	glDepthMask(1);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	if (wasLighting)
		glEnable(GL_LIGHTING);
}

void SkyRenderer::setSkySphereTexture(int texId) {
	skySphereTexture = texId;
}

void SkyRenderer::setSkyBoxTexture(int textures[6]) {
	skyBoxTexture[SKY_FRONT] = textures[SKY_FRONT];
	skyBoxTexture[SKY_LEFT] = textures[SKY_LEFT];
	skyBoxTexture[SKY_RIGHT] = textures[SKY_RIGHT];
	skyBoxTexture[SKY_BACK] = textures[SKY_BACK];
	skyBoxTexture[SKY_TOP] = textures[SKY_TOP];
	skyBoxTexture[SKY_BOTTOM] = textures[SKY_BOTTOM];
}

void SkyRenderer::setSkyType(SkyType t) {

}

int SkyRenderer::getSkyType() {
	return type;
}

int SkyRenderer::getSkySphereTexture() {
	return skySphereTexture;
}

int * SkyRenderer::getSkyBoxTexture() {
	return skyBoxTexture;
}
