#include "Camera.h"

Camera::Camera() {

}

void Camera::Initialize() {
	yaw = 0;
	pitch = 0;
	fly = false;
}

void Camera::Refresh() {
	UpdateCameraDirection();

	worldPlacement.position = transform.position;
	worldPlacement.rotation.x = 0;
	worldPlacement.rotation.y = -getYaw() * 180 / PI;
	worldPlacement.rotation.z = getPitch() * 180 / PI;

	//prevTransform = transform;

	strafex = cos(yaw - PI / 2);
	strafez = sin(yaw - PI / 2);

	glLoadIdentity();
	gluLookAt(transform.position.x, transform.position.y, transform.position.z,
		transform.position.x+transform.rotation.x, transform.position.y+transform.rotation.y, transform.position.z+transform.rotation.z,
		0, 1, 0);
}

void Camera::SetTransform(Transform t) {
	transform = t;
}

void Camera::setYaw(float f) {
	yaw = f;
}

void Camera::setPitch(float f) {
	pitch = f;
}

float Camera::getYaw() {
	return yaw;
}

float Camera::getPitch() {
	return pitch;
}

Transform Camera::getTransform() {
	return transform;
}

Transform Camera::getWorldPlacement() {
	return worldPlacement;
}

void Camera::MoveCamera(float distance) {
	UpdateCameraDirection();

	transform.position.x += distance*transform.rotation.x;
	if (fly) transform.position.y += distance*transform.rotation.y;
	transform.position.z += distance*transform.rotation.z;

	Refresh();
}

void Camera::StrafeCamera(float distance) {
	transform.position.x += distance*strafex;
	transform.position.z += distance*strafez;

	Refresh();
}

void Camera::FlyCamera(float distance) {
	transform.position.y += distance;

	Refresh();
}

void Camera::RotateCameraYaw(float angle) {
	float limit = 360 * PI / 180;

	yaw += angle;

	if (yaw < -limit)
		yaw = 0;

	if (yaw > limit)
		yaw = 0;

	Refresh();
}

void Camera::RotateCameraPitch(float angle) {
	float limit = 89 * PI / 180;

	pitch += angle;

	if (pitch < -limit)
		pitch = -limit;

	if (pitch > limit)
		pitch = limit;

	Refresh();
}

void Camera::UpdateCameraDirection() {
	transform.rotation.x = cos(yaw) * cos(pitch);
	transform.rotation.y = sin(pitch);
	transform.rotation.z = sin(yaw) * cos(pitch);
}
