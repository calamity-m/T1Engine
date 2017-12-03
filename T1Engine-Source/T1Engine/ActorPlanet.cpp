#include "ActorPlanet.h"

ActorPlanet::ActorPlanet(float rotRate, float r, Type planetType) {
	rotationRate = rotRate;
	radius = r;
	type = planetType;
}

void ActorPlanet::Initialize() {

}

void ActorPlanet::Update() {
	planetRot += rotationRate;
	planetRot = fmod(planetRot, 360);
	//planetRot = (int)planetRot % 360;
}

void ActorPlanet::Render() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	if (type == Venus) {
		GLuint texHandle = ResourceManager::getTexture(1);
		if (texHandle != -1)
			glBindTexture(GL_TEXTURE_2D, texHandle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glRotatef(planetRot, 1, 0, 1);
		glScalef(radius, radius, radius);
		Shapes::drawSphere(0.5, 35, 35);
	}

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	/*
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texHandle2);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambientPlanet);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffusePlanet);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specularPlanet);
	glMaterialf(GL_FRONT, GL_SHININESS, shinePlanet);

	glTranslatef(-45, -45, 0);

	glRotatef(-planetRot, 1, 0, 1);

	glScalef(45, 45, 45);
	drawSphereDetailed();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	
	*/
}

void ActorPlanet::setType(Type planetType) {
	type = planetType;
}
