#include "ActorPlayer.h"

ActorPlayer::ActorPlayer() {
}

ActorPlayer::ActorPlayer(Transform initialPos) {
	transform = initialPos;
	collisionRadius = 0.2;
	drawCollision = false;
	drawShip = false;
}

void ActorPlayer::Initialize() {

}

void ActorPlayer::Update() {

	prevTransform = transform;

}

void ActorPlayer::Render() {
	glPushMatrix();

	// Update our drawing call to reflect our internal position and rotations
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	if (drawCollision)
		Shapes::drawWiredSphere(collisionRadius, 15, 15);

	if (drawShip) glutWireTeapot(0.5);

	glPopMatrix();
}

void ActorPlayer::MovePlayer(Transform t) {
	transform = t;
}