#include "ActorShip.h"



ActorShip::ActorShip(int modelIndex) {
	model = ResourceManager::getModel(modelIndex);
	collisionRadius = 5;
	drawCollision = false;
}

void ActorShip::Initialize() {

}

void ActorShip::Update() {
	ringRot += 1;
	ringRot = ((int)ringRot) % 360;

	sphereRot += 3;
	sphereRot = ((int)sphereRot) % 360;
}

void ActorShip::Render() {
	glPushMatrix();
	//if (lighting)
		glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(0));
	// Translation and rotations to update our draw position/rotation to match our internal kept position/rotation
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	if (drawCollision)
		Shapes::drawWiredSphere(collisionRadius, 10, 10);

	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);

	// Draw the model
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glScalef(0.5, 0.5, 0.5);

	for (size_t i = 0; i < model.meshData.size(); i++) {
		glPushMatrix();
		glCallList(model.meshData[i].id);
		glPopMatrix();
	}
	glPopMatrix();

	// Draw rotating Spheres
	glPushMatrix();
	renderRotatingSpheres();
	glRotatef(180, 1, 0, 0);
	renderRotatingSpheres();
	glPopMatrix();

	// Draw rotating Rings
	glPushMatrix();
	renderRotatingRings();
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void ActorShip::renderRotatingSpheres()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(2));

	glRotatef(sphereRot, 0, 1, 0);
	glTranslatef(0, 4, 0);
	glScalef(5,5, 5);
	Shapes::drawSphere(0.5, 13, 13);

	glPushMatrix();

	glTranslatef(0, -0.1, 0);
	glScalef(.25, 2, .25);
	glRotatef(90, 1, 0, 0);
	Shapes::drawCylinder(0.5, 1);

	glPopMatrix();

	glPopMatrix();
}

void ActorShip::renderRotatingRings()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(2));
	// Ring 1 (Middle)
	renderRotatingRing(10, 11, 30);
	glRotatef(15, 0, 0, 1);
	renderRotatingRing(13, 11, 30);

	// Ring 2 (Front)
	glPushMatrix();
	glTranslatef(0, 0, 6);
	renderRotatingRing(9, 9, 45);
	glPopMatrix();

	// Ring 3 (Back)
	glPushMatrix();
	glTranslatef(0, 0, -6);
	renderRotatingRing(15, 13, 25);
	glPopMatrix();

	glPopMatrix();

}

void ActorShip::renderRotatingRing(float yval, float num, float rot)
{
	glPushMatrix();

	for (int i = 0; i <= num; i++) {
		renderPeg(yval);
		glRotatef(rot, 0, 0, 1);
	}

	glPopMatrix();

}

void ActorShip::renderPeg(float y)
{
	glPushMatrix();

	glRotatef(ringRot, 0, 0, 1);

	glPushMatrix();
	glTranslatef(0, y, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(.75, .75, .75);
	Shapes::drawCylinder(0.5, 3);

	glPopMatrix();

	glPopMatrix();

}
