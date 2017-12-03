#include "ActorPortal.h"

ActorPortal::ActorPortal(int modelIndex) {
	model = ResourceManager::getModel(modelIndex);
	collisionRadius = 5;
	drawCollision = false;
}

void ActorPortal::Initialize() {

}

void ActorPortal::Update() {

}

void ActorPortal::Render() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, textureId);

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

	for (size_t i = 0; i < model.meshData.size(); i++) {
		glPushMatrix();
		//a[i].name.find("tire") != std::string::npos
		if (model.meshData[i].name.find("Event_Hgrizgn") != std::string::npos) {
			glDisable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(19));
		}
		else {
			glEnable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(4));
		}
		glCallList(model.meshData[i].id);
		glPopMatrix();
	}


	glPopMatrix();

	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}
