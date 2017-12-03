#include "ActorDisplay.h"

ActorDisplay::ActorDisplay(int modelIndex, int texIndex, float rotationAmt, float cRadius) {
	model = ResourceManager::getModel(modelIndex);
	textureId = ResourceManager::getTexture(texIndex);
	rotationAmount = rotationAmt;
	rotate = false;
	drawCollision = false;
	collisionRadius = cRadius;
}

void ActorDisplay::Initialize() {

}

void ActorDisplay::Update() {
	rotation += rotationAmount;
	rotation = fmod(rotation, 360);
}

void ActorDisplay::Render() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureId);

	// Update our drawing position/rotation to reflect internal position/rotation
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	if (drawCollision)
		Shapes::drawWiredSphere(collisionRadius, 10, 10);

	glScalef(transform.scale.y, transform.scale.x, transform.scale.z);

	// Draw our model
	glPushMatrix();

	if (rotate)
		glRotatef(rotation, 0, 1, 0);

	for (size_t i = 0; i < model.meshData.size(); i++) {
		glPushMatrix();
		glCallList(model.meshData[i].id);
		glPopMatrix();
	}


	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}

float ActorDisplay::GetRotation() {
	return rotation;
}

float ActorDisplay::GetModelX()
{
	return model.meshData[0].pos.x;
}

float ActorDisplay::GetModelY()
{
	return model.meshData[0].pos.y;
}

float ActorDisplay::GetModelZ()
{
	return model.meshData[0].pos.z;
}
